/******************************************************************************
**
** Copyright (C) 2017 Ivan Pinezhaninov <ivan.pinezhaninov@gmail.com>
**
** This file is part of the IntervalTree - Red-Black balanced interval tree
** which can be found at https://github.com/IvanPinezhaninov/IntervalTree/.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
** OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
** THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
******************************************************************************/

#ifndef INTERVALTREE_H
#define INTERVALTREE_H

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <ostream>
#include <utility>
#include <vector>

namespace Intervals {

constexpr static const double VECTOR_RESERVE_RATE = 0.25;


template <typename IntervalType, typename ValueType = size_t>
struct Interval
{
    Interval(const IntervalType &a, const IntervalType &b, const ValueType &val) :
        low(std::min(a, b)),
        high(std::max(a, b)),
        value(val)
    {
    }


    Interval(const IntervalType &a, const IntervalType &b) :
        Interval(a, b, ValueType())
    {
    }


    Interval(const std::pair<IntervalType, IntervalType> &interval) :
        Interval(interval.first, interval.second)
    {
    }


    Interval(const std::pair<IntervalType, IntervalType> &interval, const ValueType &val) :
        Interval(interval.first, interval.second, val)
    {
    }


    Interval(const std::tuple<IntervalType, IntervalType> &interval) :
        Interval(std::get<0>(interval), std::get<1>(interval))
    {
    }


    Interval(const std::tuple<IntervalType, IntervalType> &interval, const ValueType &val) :
        Interval(std::get<0>(interval), std::get<1>(interval), val)
    {
    }


    Interval() = default;
    Interval(const Interval &) = default;
    Interval(Interval &&) = default;
    Interval &operator=(const Interval &) = default;
    Interval &operator=(Interval &&) = default;
    virtual ~Interval() = default;


    bool operator==(const Interval &other) const
    {
        return !(low < other.low || other.low < low
                 || high < other.high || other.high < high
                 || value < other.value || other.value < value);
    }


    bool operator<(const Interval &other) const
    {
        return (low < other.low || high < other.high);
    }


    IntervalType low;
    IntervalType high;
    ValueType value;
};


template <typename IntervalType, typename ValueType = size_t>
class IntervalTree
{
public:
    using Interval = Intervals::Interval<IntervalType, ValueType>;
    using Intervals = std::vector<Interval>;
    using size_type = std::size_t;


    IntervalTree() :
        m_nill(new Node()),
        m_root(m_nill),
        m_size(0)
    {
    }


    template <typename Container>
    IntervalTree(const Container &intervals) :
        IntervalTree()
    {
        for (const Interval &interval : intervals) {
            insert(interval);
        }
    }


    template <typename ForwardIterator>
    IntervalTree(ForwardIterator begin, ForwardIterator end) :
        IntervalTree()
    {
        while (begin != end) {
            insert(*begin);
            ++begin;
        }
    }


    virtual ~IntervalTree()
    {
        if (nullptr != m_root) {
            destroySubtree(m_root);
        }

        delete m_nill;
    }


    IntervalTree(const IntervalTree &other) :
        m_nill(new Node()),
        m_root(copySubtree(other.m_root, other.m_nill, m_nill)),
        m_size(other.m_size)
    {
    }


    IntervalTree(IntervalTree &&other) noexcept :
        m_nill(other.m_nill),
        m_root(other.m_root),
        m_size(other.m_size)
    {
        other.m_nill = nullptr;
        other.m_root = nullptr;
    }


    IntervalTree &operator=(const IntervalTree &other)
    {
        if (this != &other) {
            IntervalTree(other).swap(*this);
        }

        return *this;
    }


    IntervalTree &operator=(IntervalTree &&other) noexcept
    {
        other.swap(*this);
        return *this;
    }


    void swap(IntervalTree &other) noexcept
    {
        std::swap(m_nill, other.m_nill);
        std::swap(m_root, other.m_root);
        std::swap(m_size, other.m_size);
    }


    bool insert(const Interval &interval)
    {
        assert(nullptr != m_root && nullptr != m_nill);

        if (m_root == m_nill) {
            // Tree is empty
            assert(0 == m_size);
            m_root = new Node(interval, Color::Black, m_nill);
            m_size = 1;
            return true;
        }

        Node *node = findNode(m_root, interval);
        assert(node != m_nill);

        if (interval.low < node->intervals.front().low) {
            createChildNode(node, interval, Position::Left);
            return true;
        } else if (node->intervals.front().low < interval.low) {
            createChildNode(node, interval, Position::Right);
            return true;
        }

        if (!isNodeHasInterval(node, interval)) {
            auto it = std::lower_bound(node->intervals.begin(), node->intervals.end(), interval,
                                       [] (const Interval &lhs, const Interval &rhs) -> bool { return (lhs.high < rhs.high); });

            node->intervals.insert(it, interval);

            if (node->high < interval.high) {
                node->high = interval.high;
            }

            if (node->highest < node->high) {
                node->highest = node->high;
                insertionFixNodeLimits(node);
            }

            ++m_size;
            return true;
        }

        // Value already exists
        return false;
    }


    bool remove(const Interval &interval)
    {
        assert(nullptr != m_root && nullptr != m_nill);

        if (m_root == m_nill) {
            // Tree is empty
            assert(0 == m_size);
            return false;
        }

        Node *node = findNode(m_root, interval);
        assert(node != m_nill);

        auto it = std::find(node->intervals.begin(), node->intervals.end(), interval);
        if (it != node->intervals.cend()) {
            node->intervals.erase(it);
            if (isNodeAboutToBeDestroyed(node)) {
                Node *child = m_nill;
                if (node->right == m_nill) {
                    child = node->left;
                } else if (node->left == m_nill) {
                    child = node->right;
                } else {
                    Node *nextValueNode = node->right;
                    while (nextValueNode->left != m_nill) {
                        nextValueNode = nextValueNode->left;
                    }
                    node->intervals = std::move(nextValueNode->intervals);
                    node->high = std::move(nextValueNode->high);
                    removeFixNodeLimits(node);
                    node = nextValueNode;
                    child = nextValueNode->right;
                }

                if (child == m_nill && node->parent == m_nill) {
                    // Node is root without children
                    swapRelations(node, child);
                    destroyNode(node);
                    return true;
                }

                if (Color::Red == node->color || Color::Red == child->color) {
                    swapRelations(node, child);
                    if (Color::Red == child->color) {
                        child->color = Color::Black;
                    }
                } else {
                    assert(Color::Black == node->color);

                    if (child == m_nill) {
                        child = node;
                    } else {
                        swapRelations(node, child);
                    }

                    removeFix(child);

                    if (node->parent != m_nill) {
                        setChildNode(node->parent, m_nill, nodePosition(node));
                    }
                }

                if (node->parent != m_nill) {
                    removeFixNodeLimits(node->parent, 1);
                }
                destroyNode(node);
            } else {
                if (isEqual(interval.high, node->high)) {
                    node->high = findHighest(node->intervals);
                }

                if (isEqual(interval.high, node->highest)) {
                    removeFixNodeLimits(node);
                }

                --m_size;
            }

            return true;
        }

        // Value not found
        return false;
    }


    bool contains(const Interval &interval) const
    {
        assert(nullptr != m_root && nullptr != m_nill);

        if (m_root == m_nill) {
            // Tree is empty
            assert(0 == m_size);
            return false;
        }

        Node *node = findNode(m_root, interval);
        assert(node != m_nill);

        return isNodeHasInterval(node, interval);
    }


    Intervals intervals() const
    {
        Intervals out;
        out.reserve(m_size);

        if (m_root != m_nill) {
            subtreeIntervals(m_root, out);
        }

        return out;
    }


    void findOverlappingIntervals(const Interval &interval, Intervals &out, bool boundary = true) const
    {
        if (!out.empty()) {
            out.clear();
        }

        if (m_root != m_nill) {
            subtreeOverlappingIntervals(m_root, interval, boundary, [&out] (const Interval &in) -> void { out.push_back(in); });
        }
    }


    Intervals findOverlappingIntervals(const Interval &interval, bool boundary = true) const
    {
        Intervals out;
        out.reserve(m_size * VECTOR_RESERVE_RATE);
        findOverlappingIntervals(interval, out, boundary);
        return out;
    }


    void findInnerIntervals(const Interval &interval, Intervals &out, bool boundary = true) const
    {
        if (!out.empty()) {
            out.clear();
        }

        if (m_root != m_nill) {
            subtreeInnerIntervals(m_root, interval, boundary, [&out] (const Interval &in) -> void { out.push_back(in); });
        }
    }


    Intervals findInnerIntervals(const Interval &interval, bool boundary = true) const
    {
        Intervals out;
        out.reserve(m_size * VECTOR_RESERVE_RATE);
        findInnerIntervals(interval, out, boundary);
        return out;
    }


    void findOuterIntervals(const Interval &interval, Intervals &out, bool boundary = true) const
    {
        if (!out.empty()) {
            out.clear();
        }

        if (m_root != m_nill) {
            subtreeOuterIntervals(m_root, interval, boundary, [&out] (const Interval &in) -> void { out.push_back(in); });
        }
    }


    Intervals findOuterIntervals(const Interval &interval, bool boundary = true) const
    {
        Intervals out;
        out.reserve(m_size * VECTOR_RESERVE_RATE);
        findOuterIntervals(interval, out, boundary);
        return out;
    }


    void findIntervalsContainPoint(const IntervalType &point, Intervals &out, bool boundary = true) const
    {
        if (!out.empty()) {
            out.clear();
        }

        if (m_root != m_nill) {
            subtreeIntervalsContainPoint(m_root, point, boundary, [&out] (const Interval &in) -> void { out.push_back(in); });
        }
    }


    Intervals findIntervalsContainPoint(const IntervalType &point, bool boundary = true) const
    {
        Intervals out;
        out.reserve(m_size * VECTOR_RESERVE_RATE);
        findIntervalsContainPoint(point, out, boundary);
        return out;
    }


    size_type countOverlappingIntervals(const Interval &interval, bool boundary = true) const
    {
        size_type count = 0;

        if (m_root != m_nill) {
            subtreeOverlappingIntervals(m_root, interval, boundary, [&count] (const Interval &) -> void { ++count; });
        }

        return count;
    }


    size_type countInnerIntervals(const Interval &interval, bool boundary = true) const
    {
        size_type count = 0;

        if (m_root != m_nill) {
            subtreeInnerIntervals(m_root, interval, boundary, [&count] (const Interval &) -> void { ++count; });
        }

        return count;
    }


    size_type countOuterIntervals(const Interval &interval, bool boundary = true) const
    {
        size_type count = 0;

        if (m_root != m_nill) {
            subtreeOuterIntervals(m_root, interval, boundary, [&count] (const Interval &) -> void { ++count; });
        }

        return count;
    }


    size_type countIntervalsContainPoint(const IntervalType &point, bool boundary = true) const
    {
        size_type count = 0;

        if (m_root != m_nill) {
            subtreeIntervalsContainPoint(m_root, point, boundary, [&count] (const Interval &) -> void { ++count; });
        }

        return count;
    }


    bool isEmpty() const
    {
        return (0 == m_size);
    }


    size_type size() const
    {
        return m_size;
    }


    void clear()
    {
        assert(nullptr != m_root && nullptr != m_nill);

        destroySubtree(m_root);
        m_root = m_nill;
        m_size = 0;
    }


private:
    enum class Color : char {
        Black,
        Red
    };


    enum class Position : char {
        Left,
        Right
    };


    struct Node
    {
        Node() = default;

        Node(const Interval &interval, Color col, Node *nill) :
            color(col),
            parent(nill),
            left(nill),
            right(nill),
            high(interval.high),
            lowest(interval.low),
            highest(interval.high)
        {
            intervals.push_back(interval);
        }

        Color color = Color::Black;
        Node *parent = nullptr;
        Node *left = nullptr;
        Node *right = nullptr;

        IntervalType high;
        IntervalType lowest;
        IntervalType highest;
        Intervals intervals;
    };


    Node *copySubtree(Node *otherNode, Node *otherNill, Node *parent) const
    {
        assert(nullptr != otherNode && nullptr != otherNill && nullptr != parent);

        if (otherNode == otherNill) {
            return m_nill;
        }

        Node *node = new Node();
        node->intervals = otherNode->intervals;
        node->high = otherNode->high;
        node->lowest = otherNode->lowest;
        node->highest = otherNode->highest;
        node->color = otherNode->color;
        node->parent = parent;
        node->left = copySubtree(otherNode->left, otherNill, node);
        node->right = copySubtree(otherNode->right, otherNill, node);

        return node;
    }


    void destroySubtree(Node *node) const
    {
        assert(nullptr != node);

        if (node == m_nill) {
            return;
        }

        destroySubtree(node->left);
        destroySubtree(node->right);

        delete node;
    }


    Node *findNode(Node *node, const Interval &interval) const
    {
        assert(nullptr != node);
        assert(node != m_nill);

        Node *child = m_nill;
        if (interval.low < node->intervals.front().low) {
            child = childNode(node, Position::Left);
        } else if (node->intervals.front().low < interval.low) {
            child = childNode(node, Position::Right);
        } else {
            return node;
        }

        return (child == m_nill) ? node : findNode(child, interval);
    }


    Node *siblingNode(Node *node) const
    {
        assert(nullptr != node);

        return (Position::Left == nodePosition(node))
                ? childNode(node->parent, Position::Right)
                : childNode(node->parent, Position::Left);
    }


    Node *childNode(Node *node, Position position) const
    {
        assert(nullptr != node);

        switch (position) {
        case Position::Left:
            return node->left;
        case Position::Right:
            return node->right;
        default:
            assert(false);
            return nullptr;
        }
    }


    void setChildNode(Node *node, Node *child, Position position) const
    {
        assert(nullptr != node && nullptr != child);
        assert(node != m_nill);

        switch (position) {
        case Position::Left:
            node->left = child;
            break;
        case Position::Right:
            node->right = child;
            break;
        default:
            assert(false);
            break;
        }

        if (child != m_nill) {
            child->parent = node;
        }
    }


    Position nodePosition(Node *node) const
    {
        assert(nullptr != node && nullptr != node->parent);

        return (node->parent->left == node) ? Position::Left : Position::Right;
    }


    void createChildNode(Node *parent, const Interval &interval, Position position)
    {
        assert(nullptr != parent);
        assert(childNode(parent, position) == m_nill);

        Node *child = new Node(interval, Color::Red, m_nill);
        setChildNode(parent, child, position);
        insertionFixNodeLimits(child);
        insertionFix(child);
        ++m_size;
    }


    void destroyNode(Node *node)
    {
        --m_size;
        delete node;
    }


    void updateNodeLimits(Node *node) const
    {
        assert(nullptr != node);

        Node *left = isNodeAboutToBeDestroyed(node->left) ? m_nill : node->left;
        Node *right = isNodeAboutToBeDestroyed(node->right) ? m_nill : node->right;

        const IntervalType &lowest = (left != m_nill) ? left->lowest : node->intervals.front().low;

        if (isNotEqual(node->lowest, lowest)) {
            node->lowest = lowest;
        }

        const IntervalType &highest = std::max({ left->highest, right->highest, node->high });

        if (isNotEqual(node->highest, highest)) {
            node->highest = highest;
        }
    }


    bool isNodeAboutToBeDestroyed(Node *node) const
    {
        assert(nullptr != node);

        return (node != m_nill && node->intervals.empty());
    }


    void subtreeIntervals(Node *node, Intervals &out) const
    {
        assert(nullptr != node);

        if (node == m_nill) {
            return;
        }

        subtreeIntervals(node->left, out);

        out.insert(out.end(), node->intervals.begin(), node->intervals.end());

        subtreeIntervals(node->right, out);
    }


    template <typename Callback>
    void subtreeOverlappingIntervals(Node *node, const Interval &interval, bool boundary, Callback &&callback) const
    {
        assert(nullptr != node);

        if (node == m_nill) {
            return;
        }

        if (node->left != m_nill
                && boundary ? !(node->left->highest < interval.low) : interval.low < node->left->highest) {
            subtreeOverlappingIntervals(node->left, interval, boundary, std::forward<Callback>(callback));
        }

        if (boundary ? !(interval.high < node->intervals.front().low) : node->intervals.front().low < interval.high) {
            for (auto it = node->intervals.rbegin(); it != node->intervals.rend(); ++it) {
                if (boundary ? !(it->high < interval.low) : interval.low < it->high) {
                    callback(*it);
                } else {
                    break;
                }
            }
        }

        if (node->right != m_nill
                && boundary ? !(interval.high < node->right->lowest) : node->right->lowest < interval.high) {
            subtreeOverlappingIntervals(node->right, interval, boundary, std::forward<Callback>(callback));
        }
    }


    template <typename Callback>
    void subtreeInnerIntervals(Node *node, const Interval &interval, bool boundary, Callback &&callback) const
    {
        assert(nullptr != node);

        if (node == m_nill) {
            return;
        }

        if (boundary ? !(node->intervals.front().low < interval.low) : interval.low < node->intervals.front().low) {
            if (node->left != m_nill
                    && boundary ? !(node->left->highest < interval.low) : interval.low < node->left->highest) {
                subtreeInnerIntervals(node->left, interval, boundary, std::forward<Callback>(callback));
            }

            for (auto it = node->intervals.begin(); it != node->intervals.end(); ++it) {
                if (boundary ? !(interval.high < it->high) : it->high < interval.high) {
                    callback(*it);
                } else {
                    break;
                }
            }
        }

        if (node->right != m_nill
                && boundary ? !(interval.high < node->right->lowest) : node->right->lowest < interval.high) {
            subtreeInnerIntervals(node->right, interval, boundary, std::forward<Callback>(callback));
        }
    }


    template <typename Callback>
    void subtreeOuterIntervals(Node *node, const Interval &interval, bool boundary, Callback &&callback) const
    {
        assert(nullptr != node);

        if (node == m_nill) {
            return;
        }

        if (node->left != m_nill
                && boundary ? !(node->left->highest < interval.high) : interval.high < node->left->highest) {
            subtreeOuterIntervals(node->left, interval, boundary, std::forward<Callback>(callback));
        }

        if (boundary ? !(interval.low < node->intervals.front().low) : node->intervals.front().low < interval.low) {
            for (auto it = node->intervals.rbegin(); it != node->intervals.rend(); ++it) {
                if (boundary ? !(it->high < interval.high) : interval.high < it->high) {
                    callback(*it);
                } else {
                    break;
                }
            }

            if (node->right != m_nill
                    && boundary ? !(interval.low < node->right->lowest) : node->right->lowest < interval.low) {
                subtreeOuterIntervals(node->right, interval, boundary, std::forward<Callback>(callback));
            }
        }
    }


    template <typename Callback>
    void subtreeIntervalsContainPoint(Node *node, const IntervalType &point, bool boundary, Callback &&callback) const
    {
        assert(nullptr != node);

        if (node == m_nill) {
            return;
        }

        if (node->left != m_nill
                && boundary ? !(node->left->highest < point) : point < node->left->highest) {
            subtreeIntervalsContainPoint(node->left, point, boundary, std::forward<Callback>(callback));
        }

        if (boundary ? !(point < node->intervals.front().low) : node->intervals.front().low < point) {
            if (!(node->high < point)) {
                for (auto it = node->intervals.rbegin(); it != node->intervals.rend(); ++it) {
                    if (boundary ? !(it->high < point) : point < it->high) {
                        callback(*it);
                    } else {
                        break;
                    }
                }
            }

            if (node->right != m_nill
                    && boundary ? !(node->right->highest < point) : point < node->right->highest) {
                subtreeIntervalsContainPoint(node->right, point, boundary, std::forward<Callback>(callback));
            }
        }
    }


    bool isNodeHasInterval(Node *node, const Interval &interval) const
    {
        assert(nullptr != node);

        return (node->intervals.cend() != std::find(node->intervals.cbegin(), node->intervals.cend(), interval));
    }


    IntervalType findHighest(const Intervals &intervals) const
    {
        assert(!intervals.empty());

        auto it = std::max_element(intervals.cbegin(), intervals.cend(),
                                   [] (const Interval &lhs, const Interval &rhs) -> bool { return lhs.high < rhs.high; });

        assert(it != intervals.cend());

        return it->high;
    }


    bool isNotEqual(const IntervalType &lhs, const IntervalType &rhs) const
    {
        return (lhs < rhs || rhs < lhs);
    }


    bool isEqual(const IntervalType &lhs, const IntervalType &rhs) const
    {
        return !isNotEqual(lhs, rhs);
    }


    void swapRelations(Node *node, Node *child)
    {
        assert(nullptr != node && nullptr != child);

        if (node->parent == m_nill) {
            if (child != m_nill) {
                child->parent = m_nill;
            }
            m_root = child;
        } else {
            setChildNode(node->parent, child, nodePosition(node));
        }
    }


    void rotateCommon(Node *node, Node *child) const
    {
        assert(nullptr != node && nullptr != child);
        assert(node != m_nill && child != m_nill);

        std::swap(node->color, child->color);

        updateNodeLimits(node);

        if (child->highest < node->highest) {
            child->highest = node->highest;
        }

        if (node->lowest < child->lowest) {
            child->lowest = node->lowest;
        }
    }


    Node *rotateLeft(Node *node)
    {
        assert(nullptr != node && nullptr != node->right);

        Node *child = node->right;
        swapRelations(node, child);
        setChildNode(node, child->left, Position::Right);
        setChildNode(child, node, Position::Left);
        rotateCommon(node, child);

        return child;
    }


    Node *rotateRight(Node *node)
    {
        assert(nullptr != node && nullptr != node->left);

        Node *child = node->left;
        swapRelations(node, child);
        setChildNode(node, child->right, Position::Left);
        setChildNode(child, node, Position::Right);
        rotateCommon(node, child);

        return child;
    }


    Node *rotate(Node *node)
    {
        assert(nullptr != node);

        switch (nodePosition(node)) {
        case Position::Left:
            return rotateRight(node->parent);
        case Position::Right:
            return rotateLeft(node->parent);
        default:
            assert(false);
            return nullptr;
        }
    }


    void insertionFixNodeLimits(Node *node)
    {
        assert(nullptr != node && nullptr != node->parent);

        while (node->parent != m_nill) {
            bool finish = true;

            if (node->parent->highest < node->highest) {
                node->parent->highest = node->highest;
                finish = false;
            }

            if (node->lowest < node->parent->lowest) {
                node->parent->lowest = node->lowest;
                finish = false;
            }

            if (finish) {
                break;
            }

            node = node->parent;
        }
    }


    void removeFixNodeLimits(Node *node, size_type minRange = 0)
    {
        assert(nullptr != node && nullptr != node->parent);

        size_type range = 0;
        while (node != m_nill) {
            bool finish = (minRange < range);

            updateNodeLimits(node);

            if (isNotEqual(node->highest, node->parent->highest)) {
                finish = false;
            }

            if (isNotEqual(node->lowest, node->parent->lowest)) {
                finish = false;
            }

            if (finish) {
                break;
            }

            node = node->parent;
            ++range;
        }
    }


    void insertionFix(Node *node)
    {
        assert(nullptr != node && nullptr != node->parent);

        while (Color::Red == node->color && Color::Red == node->parent->color) {
            Node *parent = node->parent;
            Node *uncle = siblingNode(parent);
            switch (uncle->color) {
            case Color::Red:
                uncle->color = Color::Black;
                parent->color = Color::Black;
                parent->parent->color = Color::Red;
                node = parent->parent;
                break;
            case Color::Black:
                if (nodePosition(node) != nodePosition(parent)) {
                    parent = rotate(node);
                }
                node = rotate(parent);
                break;
            default:
                assert(false);
                break;
            }
        }

        if (node->parent == m_nill && Color::Black != node->color) {
            node->color = Color::Black;
        }
    }


    void removeFix(Node *node)
    {
        assert(nullptr != node && nullptr != node->parent);

        while (Color::Black == node->color && node->parent != m_nill) {
            Node *sibling = siblingNode(node);
            if (Color::Red == sibling->color) {
                rotate(sibling);
                sibling = siblingNode(node);
            }

            assert(nullptr != sibling && nullptr != sibling->left && nullptr != sibling->right);
            assert(Color::Black == sibling->color);

            if (Color::Black == sibling->left->color && Color::Black == sibling->right->color) {
                sibling->color = Color::Red;
                node = node->parent;
            } else {
                if (Position::Left == nodePosition(sibling) && Color::Black == sibling->left->color) {
                    sibling = rotateLeft(sibling);
                } else if (Position::Right == nodePosition(sibling) && Color::Black == sibling->right->color) {
                    sibling = rotateRight(sibling);
                }
                rotate(sibling);
                node = siblingNode(node->parent);
            }
        }

        if (Color::Black != node->color) {
            node->color = Color::Black;
        }
    }


    Node *m_nill;
    Node *m_root;
    size_type m_size;
};


template <typename T>
void swap(IntervalTree<T> &lhs, IntervalTree<T> &rhs)
{
    lhs.swap(rhs);
}

} // namespace Intervals


template <typename T, typename K>
std::ostream &operator<<(std::ostream &out, const Intervals::Interval<T, K> &interval) {
    out << "Interval(" << interval.low << ", " << interval.high << "): " << interval.value;
    return out;
}


template <typename T, typename K>
std::ostream &operator<<(std::ostream &out, const Intervals::IntervalTree<T, K> &tree) {
    out << "IntervalTree(" << tree.size() << ")";
    return out;
}

#endif // INTERVALTREE_H
