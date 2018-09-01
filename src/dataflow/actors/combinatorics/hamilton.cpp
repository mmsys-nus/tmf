/*
 *   TMF
 *   Copyright (C) TMF Team
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

#include "hamilton.h"

using namespace df;
using namespace std;

ActorRegister<Hamilton> Hamilton::reg("Hamilton");

Hamilton::Hamilton(const string & name) : Actor(name) {
  input = createInputPortVector<Str>("input");
  output = createOutputPortVector<Str>("output");
}

void Hamilton::init() {
  if (!propEmpty("nbnodes")) {
    nbnodes = getPropInt("nbnodes");
  } else
    nbnodes = 0;
  first = true;  
}
void Hamilton::run() {

  if (first) {
	auto out = produce(output);
  	for (auto o : out) {
  		o->set(name);
  	}
  	release(output);
	first = false;
  }

  auto in = consume(input);
  for (auto i : in) {
	string msg = *i->get();
  	if (msg.find(name)==string::npos) {
    		msg += name;

	  	if (msg.length() == nbnodes) {
    			log("Hamiltonian path: "+msg);
  		} else {
  			auto out = produce(output);
			for (auto o : out) {
				o->set(msg);
			}
  			release(output);
		}
  	}
  }
  release(input); 
}

Hamilton::~Hamilton() {
  destroyPort(input);
  destroyPort(output);
}