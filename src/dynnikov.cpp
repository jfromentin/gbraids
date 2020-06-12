/*
* This file is part of Gbraids (https://github.com/jfromentin/gbraids).
* Copyright (c) 2020 Jean Fromentin (fromentin@math.cnrs.fr).
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, version 3.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "dynnikov.hpp"

//*********************
// DynnikovCoordinates
//*********************

//--------------------------------------------
// DynnikovCoordinates::negative_Artin_action
//--------------------------------------------

void
DynnikovCoordinates::negative_Artin_action(Int& x1,Int& y1,Int& x2,Int& y2){
  Int t=x1+neg(y1)-x2-pos(y2);
  Int r1=x1-pos(y1)-pos(pos(y2)+t);
  Int r2=y2+neg(t);
  Int r3=x2-neg(y2)-neg(neg(y1)-t);
  Int r4=y1-neg(t);
  x1=r1;
  y1=r2;
  x2=r3;
  y2=r4;
}

//--------------------------------------------
// DynnikovCoordinates::positive_Artin_action
//--------------------------------------------

void
DynnikovCoordinates::positive_Artin_action(Int& x1,Int& y1,Int& x2,Int& y2){
  Int t=x1-neg(y1)-x2+pos(y2);
  Int r1=x1+pos(y1)+pos(pos(y2)-t);
  Int r2=y2-pos(t);
  Int r3=x2+neg(y2)+neg(neg(y1)+t);
  Int r4=y1+pos(t);
  x1=r1;
  y1=r2;
  x2=r3;
  y2=r4;
}
