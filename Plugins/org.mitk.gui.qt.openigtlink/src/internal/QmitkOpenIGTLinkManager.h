/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center,
Division of Medical and Biological Informatics.
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/


#ifndef QmitkOpenIGTLinkManager_h
#define QmitkOpenIGTLinkManager_h

#include <berryISelectionListener.h>

#include <QmitkAbstractView.h>

#include "ui_QmitkOpenIGTLinkManagerControls.h"
#include "mitkIGTLClient.h"
#include "mitkIGTLDeviceSource.h"

/**
  \brief OpenIGTLinkManager

  \warning  This class is not yet documented. Use "git blame" and ask the author to provide basic documentation.

  \sa QmitkAbstractView
  \ingroup ${plugin_target}_internal
*/
class QmitkOpenIGTLinkManager : public QmitkAbstractView
{
  // this is needed for all Qt objects that should have a Qt meta-object
  // (everything that derives from QObject and wants to have signal/slots)
  Q_OBJECT

  public:

    static const std::string VIEW_ID;

	QmitkOpenIGTLinkManager();
    ~QmitkOpenIGTLinkManager() override;

  public slots:
    void NewSourceByWidget(mitk::IGTLDeviceSource::Pointer source, std::string);
    void SourceSelected(mitk::IGTLDeviceSource::Pointer source);

  protected:

    void CreateQtPartControl(QWidget *parent) override;

    void SetFocus() override;

    void CreatePipeline();
    void DestroyPipeline();

    Ui::QmitkOpenIGTLinkManagerControls m_Controls;

    /** Someone needs to hold the smart pointers of new sources, otherwise the
     * objects will be lost although they are listed as microservice.
     */
    std::vector<mitk::IGTLDeviceSource::Pointer> m_AllSourcesHandledByThisWidget;

    mitk::IGTLDevice::Pointer m_CurrentIGTLDevice;
};

#endif // OpenIGTLinkManager_h
