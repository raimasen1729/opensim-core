#ifndef __SimbodyCoordinate01_05_h__
#define __SimbodyCoordinate01_05_h__

// SimbodyCoordinate01_05.h
// Author: Frank C. Anderson
/*
 * Copyright (c)  2007, Stanford University. All rights reserved. 
* Use of the OpenSim software in source form is permitted provided that the following
* conditions are met:
* 	1. The software is used only for non-commercial research and education. It may not
*     be used in relation to any commercial activity.
* 	2. The software is not distributed or redistributed.  Software distribution is allowed 
*     only through https://simtk.org/home/opensim.
* 	3. Use of the OpenSim software or derivatives must be acknowledged in all publications,
*      presentations, or documents describing work in which OpenSim or derivatives are used.
* 	4. Credits to developers may not be removed from executables
*     created from modifications of the source.
* 	5. Modifications of source code must retain the above copyright notice, this list of
*     conditions and the following disclaimer. 
* 
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
*  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
*  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
*  SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
*  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
*  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
*  OR BUSINESS INTERRUPTION) OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
*  WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


// INCLUDE
#include <iostream>
#include <string>
#include <math.h>
#include "osimSimbodyEngineDLL.h"
#include <OpenSim/Common/PropertyBool.h>
#include <OpenSim/Common/PropertyInt.h>
#include <OpenSim/Common/PropertyDbl.h>
#include <OpenSim/Common/PropertyDblArray.h>
#include <OpenSim/Common/PropertyStr.h>
#include <OpenSim/Common/PropertyStrArray.h>
#include <OpenSim/Common/PropertyObjPtr.h>
#include <OpenSim/Simulation/Model/AbstractCoordinate.h>
#include <OpenSim/Simulation/Model/AbstractTransformAxis.h>
#include <SimTKsimbody.h>

namespace OpenSim {

class SimbodyEngine01_05;

//=============================================================================
//=============================================================================
/**
 * A class implementing a Simbody generalized coordinate.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class OSIMSIMBODYENGINE_API SimbodyCoordinate01_05 : public AbstractCoordinate  
{
//=============================================================================
// DATA
//=============================================================================
protected:
	PropertyDbl _defaultValueProp;
	double &_defaultValue;

	PropertyDbl _initialValueProp;
	double &_initialValue;

	PropertyDbl _toleranceProp;
	double &_tolerance;

	PropertyDbl _stiffnessProp;
	double &_stiffness;

	PropertyDblArray _rangeProp;
	Array<double>& _range;

	PropertyStrArray _keysProp;
	Array<std::string>& _keys;

	/** Flag indicating whether the joint is clamped or not.  Clamped means
	that the coordinate is not allowed to go outside its range. */
	PropertyBool _clampedProp;
	bool &_clamped;

	/** Flag indicating whether the joint is locked or not.  Locked means
	fixed at one value. */
	PropertyBool _lockedProp;
	bool &_locked;

	/** Flag specifying what joint of coordinate this coordinate is (constrained, unconstrained). */
	PropertyInt _QTypeProp;
	int &_QType;

	PropertyObjPtr<Function> _restraintFunctionProp;
	Function *&_restraintFunction;

	PropertyObjPtr<Function> _minRestraintFunctionProp;
	Function *&_minRestraintFunction;

	PropertyObjPtr<Function> _maxRestraintFunctionProp;
	Function *&_maxRestraintFunction;

	PropertyBool _restraintActiveProp;
	bool &_restraintActive;

	PropertyObjPtr<Function> _constraintFunctionProp;
	Function *&_constraintFunction;

	/** ID of the body which this coordinate serves.  */
	SimTK::MobilizedBodyIndex _bodyId;

	/** Mobility index for this coordinate. */
	int _mobilityIndex;

	/** Motion type (rotational or translational). */
	AbstractTransformAxis::MotionType _motionType;

	/** Simbody dynamics engine that contains this coordinate. */
	SimbodyEngine01_05* _engine;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	SimbodyCoordinate01_05();
	SimbodyCoordinate01_05(const SimbodyCoordinate01_05 &aCoordinate);
	SimbodyCoordinate01_05(const AbstractCoordinate &aCoordinate);
	virtual ~SimbodyCoordinate01_05();
	virtual Object* copy() const;

	SimbodyCoordinate01_05& operator=(const SimbodyCoordinate01_05 &aCoordinate);
	void copyData(const SimbodyCoordinate01_05 &aCoordinate);
	void copyData(const AbstractCoordinate &aCoordinate);

	void setup(AbstractDynamicsEngine* aEngine);

	virtual void updateFromCoordinate(const AbstractCoordinate &aCoordinate);
	virtual double getValue() const;
	virtual bool setValue(double aValue);
	virtual bool setValue(double aValue, bool aRealize);
	virtual bool getValueUseDefault() const { return true; }
	virtual void getRange(double rRange[2]) const { rRange[0] = _range[0]; rRange[1] = _range[1]; }
	virtual bool setRange(double aRange[2]);
	virtual double getRangeMin() const { return _range[0]; }
	virtual double getRangeMax() const { return _range[1]; }
	virtual bool setRangeMin(double aMin);
	virtual bool setRangeMax(double aMax);
	virtual bool getRangeUseDefault() const { return _rangeProp.getUseDefault(); }
	virtual double getTolerance() const { return _tolerance; }
	virtual bool setTolerance(double aTolerance);
	virtual bool getToleranceUseDefault() const { return _toleranceProp.getUseDefault(); }
	virtual double getStiffness() const { return _stiffness; }
	virtual bool setStiffness(double aStiffness);
	virtual bool getStiffnessUseDefault() const { return _stiffnessProp.getUseDefault(); }
	virtual double getDefaultValue() const { return _defaultValue; }
	virtual bool setDefaultValue(double aDefaultValue);
	virtual double getInitialValue() const { return _initialValue; }
	virtual void setInitialValue(double aInitialValue);
	virtual bool getDefaultValueUseDefault() const { return _defaultValueProp.getUseDefault(); }
	virtual bool getClamped() const { return _clamped; }
	virtual bool setClamped(bool aClamped) { _clamped = aClamped; return true; }
	virtual bool getClampedUseDefault() const { return _clampedProp.getUseDefault(); }
	virtual bool getLocked() const { return _locked; }
	virtual bool setLocked(bool aLocked);
	virtual bool getLockedUseDefault() const { return _lockedProp.getUseDefault(); }
	virtual AbstractTransformAxis::MotionType getMotionType() const { return _motionType; }

	void getKeys(std::string rKeys[]) const;
	const Array<std::string>& getKeys() const { return _keys; }
   void setKeys(const OpenSim::Array<std::string>& aKeys);
	virtual bool isUsedInModel() const { return true; }
	bool isRestraintActive() const { return _restraintActive; }
	Function* getRestraintFunction() const;
	Function* getMinRestraintFunction() const;
	Function* getMaxRestraintFunction() const;
	Function* getConstraintFunction() const;
	void setConstraintFunction(const Function *function);

private:
	void setNull();
	void setupProperties();
	void determineType();
	friend class SimbodyEngine01_05;
	friend class SimbodyEngine;

//=============================================================================
};	// END of class SimbodyCoordinate01_05
//=============================================================================
//=============================================================================

} // end of namespace OpenSim

#endif // __SimbodyCoordinate01_05_h__


