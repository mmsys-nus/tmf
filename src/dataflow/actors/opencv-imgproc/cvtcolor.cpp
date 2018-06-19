/*
 *   DF
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

#include "cvtcolor.h"

using namespace df;
using namespace std;

ActorRegister<CvtColor> CvtColor::reg("CvtColor");

CvtColor::CvtColor(const string& name) : Actor(name) {
  input = createInputPort<cv::Mat>("input");
  output = createOutputPort<cv::Mat>("output");
}

void CvtColor::init() {

}

void CvtColor::run() {

  cv::Mat * in = consume(input);
  cv::Mat * out = produce(output);
  cv::cvtColor(*in, *out, CV_BGR2GRAY);
  log("sending frame "+to_string(stepno));
  release(input);
  release(output);

}

CvtColor::~CvtColor() {
  destroyPort(input);
  destroyPort(output);
}