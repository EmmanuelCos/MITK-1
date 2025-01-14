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

#ifndef _QMITKVIEWINITIALIZATIONVIEW_H_INCLUDED
#define _QMITKVIEWINITIALIZATIONVIEW_H_INCLUDED

#include <QmitkAbstractView.h>
#include <mitkILifecycleAwarePart.h>

#include "vtkRenderWindow.h"
#include <string>

#include "ui_QmitkViewInitializationViewControls.h"

class QmitkViewInitializationView : public QmitkAbstractView, public mitk::ILifecycleAwarePart
{
  // this is needed for all Qt objects that should have a MOC object (everything that derives from QObject)
  Q_OBJECT

public:
  static const std::string VIEW_ID;

  QmitkViewInitializationView();
  ~QmitkViewInitializationView() override;

  void CreateQtPartControl(QWidget *parent) override;

  void SetFocus() override;

  /// \brief Creation of the connections of main and control widget
  virtual void CreateConnections();

private:
  vtkRenderWindow *GetSelectedRenderWindow();

  void InitRenderWindowSelector();

  void UpdateRendererList();

  void Activated() override;
  void Deactivated() override;
  void Visible() override;
  void Hidden() override;

private slots:

  virtual void OnApply();

  virtual void OnResetAll();

private:
  Ui::QmitkViewInitializationViewControls *m_Controls;

  unsigned long m_CommandTag;
};

#endif // _QMITKVIEWINITIALIZATIONVIEW_H_INCLUDED
