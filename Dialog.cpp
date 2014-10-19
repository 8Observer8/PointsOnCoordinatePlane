#include <QVector>
#include <QMessageBox>
#include <QDebug>
#include "Dialog.h"
#include "ui_Dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    m_nrows( 10 ),
    m_ncols( 2 ),
    m_model( m_nrows, m_ncols, this )
{
    ui->setupUi(this);
    this->setFixedSize( this->size() );

    // Set Header
    m_model.setHeaderData( 0, Qt::Horizontal, "x" );
    m_model.setHeaderData( 1, Qt::Horizontal, "y" );

    ui->tableView->setModel( &m_model );

    QModelIndex index;
    for( int row = 0; row < m_nrows; ++row ) {
        for( int col = 0; col < m_ncols; ++col ) {
            index = m_model.index( row, col );
            m_model.setData( index, QString::number( row + 1 ) + ".0" );
        }
    }

    connect( &m_model, SIGNAL( dataChanged( QModelIndex, QModelIndex ) ),
             this, SLOT( slotDrawPlot( QModelIndex, QModelIndex ) ) );

    slotDrawPlot();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::slotDrawPlot( const QModelIndex &,
                           const QModelIndex & )
{
    QVector<double> x( m_nrows ), y( m_nrows ); // initialize with entries 0..100

    QModelIndex index;
    for( int row = 0; row < m_nrows; ++row ) {
        double value;
        bool ok = true;

        // x
        index = m_model.index( row, 0 );
        value = m_model.data( index ).toDouble( &ok );
        if ( ok ) {
            x[row] = value;
        } else {
            QMessageBox::critical( this, tr( "Error" ), tr( "Error: you have incorrect value in the table." ) );
            return;
        }

        // y
        index = m_model.index( row, 1 );
        value = m_model.data( index ).toDouble( &ok );
        if ( ok ) {
            y[row] = value;
        } else {
            QMessageBox::critical( this, tr( "Error" ), tr( "Error: you have incorrect value in the table." ) );
            return;
        }
    }

    // Create graph and assign data to it:
    ui->plotWidget->addGraph();
    ui->plotWidget->graph( 0 )->setData( x, y );

    // Give the axes some labels:
    ui->plotWidget->xAxis->setLabel( "x" );
    ui->plotWidget->yAxis->setLabel( "y" );

    // Set axes ranges, so we see all data:
    ui->plotWidget->xAxis->setRange( 0, 10 );
    ui->plotWidget->yAxis->setRange( 0, 10 );

    ui->plotWidget->replot();
}
