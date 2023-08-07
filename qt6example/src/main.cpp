#include <QApplication>
#include "darkstyle.h"
#include "framelesswindow.h"
#include "xmw.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  QApplication::setStyle(new DarkStyle);

  FramelessWindow framelessWindow;
  framelessWindow.setWindowTitle("Qt6 Frameless Window");
  framelessWindow.setWindowIcon(
    app.style()->standardIcon(QStyle::SP_DesktopIcon));

  //MainWindow *mainWindow = new MainWindow;
  Xmw *xmw = new Xmw;
  //mainWindow->show();

  framelessWindow.setContent(xmw);
  framelessWindow.show();
  return app.exec();
}
