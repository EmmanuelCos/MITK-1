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

#include "berryWorkbenchWindowConfigurer.h"

#include "berryWorkbenchWindow.h"
#include "berryImageDescriptor.h"
#include "berryWorkbench.h"
#include "berryWorkbenchPage.h"
#include "berryEditorSashContainer.h"
#include "berryWorkbenchPlugin.h"

#include "berryQtDnDControlWidget.h"

namespace berry
{

WorkbenchWindowConfigurer::WindowActionBarConfigurer::WindowActionBarConfigurer(WorkbenchWindow::WeakPtr wnd)
: window(wnd)
{

}

void WorkbenchWindowConfigurer::WindowActionBarConfigurer::SetProxy(IActionBarConfigurer::Pointer proxy)
{
  this->proxy = proxy;
}

IWorkbenchWindowConfigurer::Pointer WorkbenchWindowConfigurer::WindowActionBarConfigurer::GetWindowConfigurer()
{
  return WorkbenchWindow::Pointer(window)->GetWindowConfigurer();
}

void* WorkbenchWindowConfigurer::WindowActionBarConfigurer::GetMenuManager()
{
  if (proxy.IsNotNull())
  {
    return proxy->GetMenuManager();
  }
  //TODO window menu manager
  //return window->GetMenuManager();
  return 0;
}

WorkbenchWindowConfigurer::WorkbenchWindowConfigurer(WorkbenchWindow::Pointer window)
 : shellStyle(0), showPerspectiveBar(false), showStatusLine(true), showToolBar(true),
   showMenuBar(true), showProgressIndicator(false), initialSize(1024,768)
{
  if (window.IsNull())
  {
    throw Poco::InvalidArgumentException();
  }
  this->window = window;
  windowTitle = "BlueBerry Application";
}

IWorkbenchWindow::Pointer WorkbenchWindowConfigurer::GetWindow()
{
  return IWorkbenchWindow::Pointer(window);
}

IWorkbenchConfigurer::Pointer WorkbenchWindowConfigurer::GetWorkbenchConfigurer()
{
  return dynamic_cast<Workbench*>(PlatformUI::GetWorkbench())->GetWorkbenchConfigurer();
}

std::string WorkbenchWindowConfigurer::BasicGetTitle()
{
  return windowTitle;
}

std::string WorkbenchWindowConfigurer::GetTitle()
{
  Shell::Pointer shell = window.Lock()->GetShell();
  if (shell)
  {
    // update the cached title
    windowTitle = shell->GetText();
  }
  return windowTitle;
}

void WorkbenchWindowConfigurer::SetTitle(const std::string& title)
{
  windowTitle = title;
  Shell::Pointer shell = window.Lock()->GetShell();
  if (shell)
  {
    shell->SetText(title);
  }
}

bool WorkbenchWindowConfigurer::GetShowMenuBar()
{
  return showMenuBar;
}

void WorkbenchWindowConfigurer::SetShowMenuBar(bool show)
{
  showMenuBar = show;
//  WorkbenchWindow win = (WorkbenchWindow) getWindow();
//  Shell shell = win.getShell();
//  if (shell != null)
//  {
//    boolean showing = shell.getMenuBar() != null;
//    if (show != showing)
//    {
//      if (show)
//      {
//        shell.setMenuBar(win.getMenuBarManager().getMenu());
//      }
//      else
//      {
//        shell.setMenuBar(null);
//      }
//    }
//  }
}

bool WorkbenchWindowConfigurer::GetShowCoolBar()
{
  return showToolBar;
}

void WorkbenchWindowConfigurer::SetShowCoolBar(bool show)
{
  showToolBar = show;
  //window.setCoolBarVisible(show);
  // @issue need to be able to reconfigure after window's controls created
}

bool WorkbenchWindowConfigurer::GetShowPerspectiveBar()
{
  return showPerspectiveBar;
}

void WorkbenchWindowConfigurer::SetShowPerspectiveBar(bool show)
{
  showPerspectiveBar = show;
  //window.setPerspectiveBarVisible(show);
  // @issue need to be able to reconfigure after window's controls created
}

bool WorkbenchWindowConfigurer::GetShowStatusLine()
{
  return showStatusLine;
}

void WorkbenchWindowConfigurer::SetShowStatusLine(bool show)
{
  showStatusLine = show;
  // @issue need to be able to reconfigure after window's controls created
}

bool WorkbenchWindowConfigurer::GetShowProgressIndicator()
{
  return showProgressIndicator;
}

void WorkbenchWindowConfigurer::SetShowProgressIndicator(bool show)
{
  showProgressIndicator = show;
  // @issue need to be able to reconfigure after window's controls created
}

void WorkbenchWindowConfigurer::AddEditorAreaTransfer(const QStringList& transfers)
{
  if (transfers.isEmpty()) return;

  int oldSize = transferTypes.size();
  transferTypes.unite(QSet<QString>::fromList(transfers));

  if (transferTypes.size() == oldSize) return;

  WorkbenchPage::Pointer page = window.Lock()->GetActivePage().Cast<WorkbenchPage>();
  if (page)
  {
    QtDnDControlWidget* dropTarget =
        static_cast<QtDnDControlWidget*>(page->GetEditorPresentation()->GetLayoutPart().Cast<EditorSashContainer>()->GetParent());
    dropTarget->SetTransferTypes(transferTypes.toList());
  }
}

void WorkbenchWindowConfigurer::ConfigureEditorAreaDropListener(const IDropTargetListener::Pointer& listener)
{
  if (listener == 0) return;
  dropTargetListener = listener;

  WorkbenchPage::Pointer page = window.Lock()->GetActivePage().Cast<WorkbenchPage>();
  if (page)
  {
    QtDnDControlWidget* dropTarget =
        static_cast<QtDnDControlWidget*>(page->GetEditorPresentation()->GetLayoutPart().Cast<EditorSashContainer>()->GetParent());
    dropTarget->AddDropListener(listener.GetPointer());
  }
}

QStringList WorkbenchWindowConfigurer::GetTransfers() const
{
  return transferTypes.toList();
}

IDropTargetListener::Pointer WorkbenchWindowConfigurer::GetDropTargetListener() const
{
  return dropTargetListener;
}

IActionBarConfigurer::Pointer WorkbenchWindowConfigurer::GetActionBarConfigurer()
{
  if (actionBarConfigurer.IsNull())
  {
    // lazily initialize
    actionBarConfigurer = new WindowActionBarConfigurer(window);
  }
  return actionBarConfigurer;
}

int WorkbenchWindowConfigurer::GetShellStyle()
{
  return shellStyle;
}

void WorkbenchWindowConfigurer::SetShellStyle(int shellStyle)
{
  this->shellStyle = shellStyle;
}

Point WorkbenchWindowConfigurer::GetInitialSize()
{
  return initialSize;
}

void WorkbenchWindowConfigurer::SetInitialSize(Point size)
{
  initialSize = size;
}

void WorkbenchWindowConfigurer::CreateDefaultContents(Shell::Pointer shell)
{
  WorkbenchWindow::Pointer(window)->CreateDefaultContents(shell);
}

void* WorkbenchWindowConfigurer::CreatePageComposite(void* parent)
{
  return WorkbenchWindow::Pointer(window)->CreatePageComposite(parent);
}

bool WorkbenchWindowConfigurer::SaveState(IMemento::Pointer memento)
{
  return WorkbenchWindow::Pointer(window)->SaveState(memento);
}

}
