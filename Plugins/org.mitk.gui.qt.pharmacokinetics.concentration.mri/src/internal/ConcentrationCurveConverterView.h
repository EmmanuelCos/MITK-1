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

#ifndef ConcentrationCurveConverterView_h
#define ConcentrationCurveConverterView_h

#include <QString>

#include <QmitkAbstractView.h>
#include "ui_ConcentrationCurveConverterViewControls.h"

#include <mitkImage.h>


/*!
 *	@brief Test Plugin for SUV calculations of PET images
 */
class ConcentrationCurveConverterView : public QmitkAbstractView
{
	Q_OBJECT

public:
//    typedef itk::Image<unsigned short,3> ImageType;
    typedef itk::Image<double,3> ConvertedImageType;


	/*! @brief The view's unique ID - required by MITK */
	static const std::string VIEW_ID;

  ConcentrationCurveConverterView();

protected slots:

	/*!
	 *	@brief	Is triggered of the update button is clicked and the selected node should get the (new) iso level set.
	 */
    void OnConvertToConcentrationButtonClicked();
    void OnSettingChanged();
    bool CheckSettings() const;



protected:

	// Overridden base class functions

	/*!
	 *	@brief					Sets up the UI controls and connects the slots and signals. Gets
	 *							called by the framework to create the GUI at the right time.
	 *	@param[in,out] parent	The parent QWidget, as this class itself is not a QWidget
	 *							subclass.
	 */
	void CreateQtPartControl(QWidget* parent) override;

	/*!
	 *	@brief	Sets the focus to the plot curve button. Gets called by the framework to set the
	 *			focus on the right widget.
	 */
	void SetFocus() override;

    /*! Helper method that adds an concentration image as child node to the current m_selectedNode and returns this new child node.*/
    mitk::DataNode::Pointer AddConcentrationImage(mitk::Image* image, std::string nodeName) const;


  /*! \brief called by QmitkFunctionality when DataManager's selection has changed
  */
  void OnSelectionChanged( berry::IWorkbenchPart::Pointer source,
    const QList<mitk::DataNode::Pointer>& nodes) override;

	// Variables

	/*! @brief The view's UI controls */
    Ui::ConcentrationCurveConverterViewControls m_Controls;

    mitk::DataNode::Pointer m_selectedNode;
    mitk::Image::Pointer m_selectedImage;
    mitk::DataNode::Pointer m_selectedBaselineNode;
    mitk::Image::Pointer m_selectedBaselineImage;

private:

    /**Converts the selected image to a concentration image based on the given gui settings.*/
    mitk::Image::Pointer Convert4DConcentrationImage(mitk::Image::Pointer inputImage);
    mitk::Image::Pointer Convert3DConcentrationImage(mitk::Image::Pointer inputImage, mitk::Image::Pointer baselineImage);

    mitk::Image::Pointer ConvertT2ConcentrationImgage(mitk::Image::Pointer inputImage);

};

#endif
