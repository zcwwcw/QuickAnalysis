#include "centralwidget.h"

CentralWidget::CentralWidget(QWidget *parent) :
    QTabWidget(parent),m_proFileWidget(NULL), m_solutionWidget(NULL),m_modelWidget(NULL)
{

}

bool CentralWidget::setProFile(const QString &proFilePath)
{
    if(m_proFileWidget == NULL)
    {
        if(!QFile::exists(proFilePath))
        {
            return false;
        }
        QFile proFile(proFilePath);
        if(!proFile.open(QIODevice::ReadOnly))
        {
            return false;
        }

        QFileInfo fileInfo(proFilePath);
        QString fileName = fileInfo.fileName();
        m_proFileWidget = new QPlainTextEdit(this);
        m_proFileWidget->setReadOnly(true);
        QFont font = m_proFileWidget->font();
        font.setPixelSize(20);
        m_proFileWidget->setFont(font);
        this->addTab(m_proFileWidget, fileName);

        QString text = proFile.readAll().data();
        m_proFileWidget->setPlainText(text);
        proFile.close();
        initTmpPlotAndGL();
    }
    return true;
}

void CentralWidget::initTmpPlotAndGL()
{
    QwtPlot *plot = new QwtPlot(this);
    plot->setTitle( "Plot Demo" );
    plot->setCanvasBackground( Qt::white );
    plot->setAxisScale( QwtPlot::yLeft, 0.0, 10.0 );

    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->attach( plot );

    QwtPlotCurve *curve = new QwtPlotCurve();
    curve->setTitle( "Some Points" );
    curve->setPen( Qt::blue, 4 ),
    curve->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QPolygonF points;
    points << QPointF( 0.0, 4.4 ) << QPointF( 1.0, 3.0 )
        << QPointF( 2.0, 4.5 ) << QPointF( 3.0, 6.8 )
        << QPointF( 4.0, 7.9 ) << QPointF( 5.0, 7.1 );
    curve->setSamples( points );
    curve->attach( plot );
    this->addTab(plot, tr("Tmp Plot"));

    MyGLWidget *widget = new MyGLWidget(this);
    this->addTab(widget, tr("Tmp OpenGL"));
}
