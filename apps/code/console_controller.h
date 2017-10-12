#ifndef CODE_CONSOLE_CONTROLLER_H
#define CODE_CONSOLE_CONTROLLER_H

#include <escher.h>
#include <escher/text_field_delegate.h>
#include "console_store.h"
#include "console_line_cell.h"
#include "console_edit_cell.h"

namespace Code {

class ConsoleController : public ViewController, public ListViewDataSource, public ScrollViewDataSource, public TextFieldDelegate {
public:
  ConsoleController(Responder * parentResponder);
  ~ConsoleController();
  ConsoleController(const ConsoleController& other) = delete;
  ConsoleController(ConsoleController&& other) = delete;
  ConsoleController operator=(const ConsoleController& other) = delete;
  ConsoleController& operator=(ConsoleController&& other) = delete;

  // ViewController
  View * view() override { return &m_tableView; }
  void viewWillAppear() override;
  void didBecomeFirstResponder() override;

  // ListViewDataSource
  int numberOfRows() override;
  KDCoordinate rowHeight(int j) override;
  KDCoordinate cumulatedHeightFromIndex(int j) override;
  int indexFromCumulatedHeight(KDCoordinate offsetY) override;
  HighlightCell * reusableCell(int index, int type) override;
  int reusableCellCount(int type) override;
  int typeAtLocation(int i, int j) override;
  void willDisplayCellAtLocation(HighlightCell * cell, int i, int j) override;

  // TextFieldDelegate
  bool textFieldShouldFinishEditing(TextField * textField, Ion::Events::Event event) override;
  bool textFieldDidReceiveEvent(TextField * textField, Ion::Events::Event event) override;
  bool textFieldDidFinishEditing(TextField * textField, const char * text, Ion::Events::Event event) override;
  Toolbox * toolboxForTextField(TextField * textFied) override;

  // Python
  void initPython();
  void executePython(const char * str);
  void stopPython();

  // Other
  static constexpr KDText::FontSize k_fontSize = KDText::FontSize::Large;
private:
  static constexpr int LineCellType = 0;
  static constexpr int EditCellType = 1;
  static constexpr int k_numberOfLineCells = 15; // May change depending on the height
  int m_rowHeight;
  ConsoleStore m_consoleStore;
  TableView m_tableView;
  ConsoleLineCell m_cells[k_numberOfLineCells];
  ConsoleEditCell m_editCell;
  char * m_pythonHeap;
};
}

#endif
