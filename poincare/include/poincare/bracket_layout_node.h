#ifndef POINCARE_BRACKET_LAYOUT_NODE_H
#define POINCARE_BRACKET_LAYOUT_NODE_H

#include <poincare/layout_cursor.h>
#include <poincare/layout_node.h>
#include <poincare/layout_reference.h>

namespace Poincare {

class BracketLayoutNode : public LayoutNode {
public:
  BracketLayoutNode() :
    LayoutNode(),
    m_childHeightComputed(false),
    m_childHeight(0)
  {}

  // LayoutNode
  void moveCursorLeft(LayoutCursor * cursor, bool * shouldRecomputeLayout) override;
  void moveCursorRight(LayoutCursor * cursor, bool * shouldRecomputeLayout) override;
  void invalidAllSizesPositionsAndBaselines() override;

  // TreeNode
  size_t size() const override { return sizeof(BracketLayoutNode); }
#if TREE_LOG
  const char * description() const override { return "BracketLayout"; }
#endif

protected:
  // LayoutNode
  void computeBaseline() override;
  KDPoint positionOfChild(LayoutNode * child) override;
  KDCoordinate childHeight();
  void computeChildHeight();
  bool m_childHeightComputed;
  uint16_t m_childHeight;
};
}

#endif