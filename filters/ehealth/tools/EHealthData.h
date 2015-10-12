/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2015  <copyright holder> <email>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#ifndef EHEALTHDATA_H
#define EHEALTHDATA_H

#include <map>
#include <string>

class Time {
public:
  int year;
  int month;
  int day;
  int hour;
  int minute;
  std::string toString() {
    return year + "-" + month + "-" + day + "-" + hour + "-" + minute;
  }
};

std::string mapToJSON(map<std::string, std::string> data) {
  std::string res = "{ ";
  for (auto& x: data) {
            res += x.first + ":" + x.second + ",";
  }
  res.pop_back();
  res += "}";
  return res;
}

class EHealthData
{
protected:
  std::string dataType;
  Time t;
public:
  EHealthData() {}
  virtual std::string toJSON()=0;
  ~EHealthData() {}
}; 

class TemperatureData: public EHealthData {
private:
  float temperature;
public:
  TemperatureData() {
    dataType = "temperature";
    temperature = 0;
  }
  std::string toJSON() {
    map<std::string, std::string> data;
    data["user"] = "ehealth";
    data["type"] = dataType;
    data["temperature"] = std::to_string(temperature);
    data["time"] = t.toString();
    return mapToJSON(data);
  }
  ~TemperatureData();
};

class PulsioximeterData: public EHealthData {
private:
  int bpm;
  int oxygen;
public:
  PulsioximeterData() {
    dataType = "pulsioximeter";
    bpm=0;
    oxygen=0;
  }
  std::string toJSON() {
    map<std::string, std::string> data;
    data["user"] = "ehealth";
    data["type"] = dataType;
    data["bpm"] = std::to_string(bpm);
    data["bpm"] = std::to_string(oxygen);
    data["time"] = t.toString();
    return mapToJSON(data);
  }
};

class ECGData: public EHealthData {
private:
  float ecg;
public:
  ECGData() {
    dataType = "ecg";
    ecg = 0;
  }
  std::string toJSON() {
    map<std::string, std::string> data;
    data["user"] = "ehealth";
    data["type"] = dataType;
    data["ecg"] = std::to_string(ecg);
    data["time"] = t.toString();
    return mapToJSON(data);
  }
};

class EMGData : public EHealthData {
private:
  int emg;
public:
  EMGData() {
    dataType = "emg";
    emg = 0;
  }
  std::string toJSON() {
    map<std::string, std::string> data;
    data["user"] = "ehealth";
    data["type"] = dataType;
    data["emg"] = std::to_string(emg);
    data["time"] = t.toString();
    return mapToJSON(data);
  }
};

class AirflowData : public EHealthData {
private:
  int airflow;
public:
  AirflowData() {
    dataType = "airflow";
    airflow = 0;
  }
  std::string toJSON() {
    map<std::string, std::string> data;
    data["user"] = "ehealth";
    data["type"] = dataType;
    data["airflow"] = std::to_string(airflow);
    data["time"] = t.toString();
    return mapToJSON(data);
  }
};

class PositionData: public EHealthData {
private:
  uint8_t position;
public:
  PositionData() {
    dataType = "position";
    position = -1;
  }
  std::string toJSON() {
    map<std::string, std::string> data;
    data["user"] = "ehealth";
    data["type"] = dataType;
    data["position"] = positionToString(position);
    data["time"] = t.toString();
    return mapToJSON(data);
  }
  static std::string positionToString( uint8_t position) {
    switch(position) {
      case 1:
	return std::string("Prone position");
      case 2:
	return std::string("Stand or sit position");
      case 3:
	return std::string("Left lateral decubitus");
      case 4:
	return std::string("Supine position");
      case 5:
	return std::string("Rigth lateral decubitus");
      default:
	return std::string("non-defined position");
    }
  }
};

class GalvanicData : public EHealthData {
private:
  float conductance;
  float resistance;
  float voltage;
public:
  GalvanicData() {
    dataType = "galvanic";
    conductance = 0;
    resistance = 0;
    voltage = 0;
  }
  std::string toJSON() {
    map<std::string, std::string> data;
    data["user"] = "ehealth";
    data["type"] = dataType;
    data["conductance"] = std::to_string(conductance);
    data["resistance"] = std::to_string(resistance);
    data["voltage"] = std::to_string(voltage);
    data["time"] = t.toString();
    return mapToJSON(data);
  }
};

class BloodPressureData : public EHealthData {
private:
  int systolic;
  int diastolic;
  int pulse;
public:
  BloodPressureData() {
    dataType = "bloodpressure";
    systolic = 0;
    diastolic = 0;
    pulse = 0;
  }
  std::string toJSON() {
    map<std::string, std::string> data;
    data["user"] = "ehealth";
    data["type"] = dataType;
    data["systolic"] = std::to_string(systolic);
    data["diastolic"] = std::to_string(diastolic);
    data["pulse"] = std::to_string(pulse);
    data["time"] = t.toString();
    return mapToJSON(data);
  }
  
};

class GlucometerData: public EHealthData {
private:
  int glucose;
public:
  GlucometerData() {
    dataType = "glucometer";
    glucose = 0;
  }
  std::string toJSON() {
    map<std::string, std::string> data;
    data["user"] = "ehealth";
    data["type"] = dataType;
    data["glucose"] = std::to_string(glucose);
    data["time"] = t.toString();
    return mapToJSON(data);
  }
};

#endif // EHEALTHDATA_H
