/*
 *   libdataflow
 *   Copyright (C) 2018
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DF_VIDEOWRITER_H_
#define DF_VIDEOWRITER_H_

#include "core/df.h"
#include "tokens/opencv/mat.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

class VideoWriter: public df::Actor {
  
private:

  std::string file_name;
  cv::Mat frame;
  df::InputPort<df::Mat> * input;
 
  cv::VideoWriter * video;

  static  df::ActorRegister<VideoWriter> reg;
public:
  
  VideoWriter(const string& name);
  
  virtual void init();
  
  virtual void run();
  
  virtual ~VideoWriter();
  
};

#endif /* DF_VIDEOWRITER_H_ */
