#ifndef GUIDEGRID_H_
#define GUIDEGRID_H_

#include <qwidget.h>
#include <qdialog.h>
#include <qstring.h>
#include <qpixmap.h>
#include <qdatetime.h>
#include <vector>

using namespace std;

class QFont;
class ProgramInfo;
class TimeInfo;
class ChannelInfo;
class MythContext;
class Settings;

namespace libmyth 
{

#define DISPLAY_CHANS 6
#define DISPLAY_TIMES 30

class GuideGrid : public QDialog
{
    Q_OBJECT
  public:
    GuideGrid(MythContext *context, const QString &channel, 
              QWidget *parent = 0, const char *name = 0);
   ~GuideGrid();

    QString getLastChannel(void);

  signals:
    void killTheApp();

  protected slots:
    void cursorLeft();
    void cursorRight();
    void cursorDown();
    void cursorUp();

    void scrollLeft();
    void scrollRight();
    void scrollDown();
    void scrollUp();

    void enter();
    void escape();

    void displayInfo();

  protected:
    void paintEvent(QPaintEvent *);

  private:
    void paintDate(QPainter *p);
    void paintChannels(QPainter *p);
    void paintTimes(QPainter *p);
    void paintPrograms(QPainter *p);
    void paintTitle(QPainter *p);

    QRect fullRect() const;
    QRect dateRect() const;
    QRect channelRect() const;
    QRect timeRect() const;
    QRect programRect() const;
    QRect titleRect() const;

    void fillChannelInfos();

    void fillTimeInfos();

    ProgramInfo *getProgramInfo(unsigned int row, unsigned int col);
    void fillProgramInfos(void);

    QBrush getBGColor(const QString &category);
    
    QFont *m_timeFont;
    QFont *m_chanFont;
    QFont *m_progFont;
    QFont *m_titleFont;

    vector<ChannelInfo> m_channelInfos;
    TimeInfo *m_timeInfos[DISPLAY_TIMES];
    ProgramInfo *m_programInfos[DISPLAY_CHANS][DISPLAY_TIMES];

    QDateTime m_originalStartTime;
    QDateTime m_currentStartTime;
    unsigned int m_currentStartChannel;
    QString m_startChanStr;
    
    int m_currentRow;
    int m_currentCol;

    bool selectState;
    bool showInfo;

    int screenwidth, screenheight;
    float wmult, hmult;

    bool showtitle;
    bool usetheme;
    QColor fgcolor;
    QColor bgcolor;

    MythContext *m_context;
    Settings *m_settings;
};

}
#endif
