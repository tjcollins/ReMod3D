// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "ModuleSensor.h"
class ASuperBotModule;
/**
 * 
 */
class REBOTS_API ModuleFloatSensor : public ModuleSensor
{
private:
	int Name; /**< name of sensor */
public:
	/**
	* @brief get the current  value of the sensor
	* @return current floating point value of the sensor
	*/
	virtual float GetFloatValue(ASuperBotModule* M) { return 0.0; };
	/**
	* @brief set sensor name
	* @param name sensor name
	*/
	void SetName(int name);
	/**
	* @brief get sensor name
	* @return sensor name
	*/
	int GetName();
	/**
	* @brief constructor
	* @param name name of sensor
	*/
	ModuleFloatSensor(int name);
	/**
	* @brief constructor
	*/
	ModuleFloatSensor();
	/**
	* @brief detructor
	*/
	virtual ~ModuleFloatSensor();
};
