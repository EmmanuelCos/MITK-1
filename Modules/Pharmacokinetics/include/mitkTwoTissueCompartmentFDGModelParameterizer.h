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

#ifndef MITKTWOTISSUECOMPARTMENTFDGMODELPARAMETERIZER_H
#define MITKTWOTISSUECOMPARTMENTFDGMODELPARAMETERIZER_H

#include "mitkAIFBasedModelParameterizerBase.h"
#include "mitkTwoTissueCompartmentFDGModel.h"

#include "MitkPharmacokineticsExports.h"

namespace mitk
{

  class MITKPHARMACOKINETICS_EXPORT TwoTissueCompartmentFDGModelParameterizer : public
    mitk::AIFBasedModelParameterizerBase<mitk::TwoTissueCompartmentFDGModel>
  {
  public:
    typedef TwoTissueCompartmentFDGModelParameterizer Self;
    typedef mitk::AIFBasedModelParameterizerBase<mitk::TwoTissueCompartmentFDGModel> Superclass;
    typedef itk::SmartPointer< Self >                            Pointer;
    typedef itk::SmartPointer< const Self >                      ConstPointer;

    itkTypeMacro(TwoTissueCompartmentFDGModelParameterizer,
                 mitk::AIFBasedModelParameterizerBase<mitk::TwoTissueCompartmentFDGModel>);
    itkFactorylessNewMacro(Self);

    typedef Superclass::ModelBaseType ModelBaseType;
    typedef Superclass::ModelBasePointer ModelBasePointer;

    typedef Superclass::ModelType ModelType;
    typedef ModelType::Pointer ModelPointer;

    typedef Superclass::StaticParameterValueType StaticParameterValueType;
    typedef Superclass::StaticParameterValuesType StaticParameterValuesType;
    typedef Superclass::StaticParameterMapType StaticParameterMapType;

    typedef Superclass::IndexType IndexType;

    /** This function returns the default parameterization (e.g. initial parametrization for fitting)
     defined by the model developer for  for the given model.*/
    ParametersType GetDefaultInitialParameterization() const override;

  protected:
    TwoTissueCompartmentFDGModelParameterizer();

    ~TwoTissueCompartmentFDGModelParameterizer() override;

  private:

    //No copy constructor allowed
    TwoTissueCompartmentFDGModelParameterizer(const Self& source);
    void operator=(const Self&);  //purposely not implemented
  };
}
#endif
