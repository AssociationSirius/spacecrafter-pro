/*
 * Spacecrafter astronomy simulation and visualization
 *
 * Copyright (C) 2021 Jérémy Calvo
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * Spacecrafter is a free open project of of LSS team
 * See the TRADEMARKS file for free open project usage requirements.
 *
 */

#include "bodyModule/solarsystem_selected.hpp"
#include "bodyModule/ssystem_iterator.hpp"
#include "bodyModule/solarsystem.hpp"
#include "tools/object.hpp"

SolarSystemSelected::SolarSystemSelected(ProtoSystem * _ssystem)
{
    ssystem = _ssystem;
}

SolarSystemSelected::~SolarSystemSelected()
{
	// release selected:
	selected = Object();
}

void SolarSystemSelected::setSelected(const Object &obj)
{
    const bool flagPlanetsOrbits_ = flagPlanetsOrbits;
    const bool flagSatellitesOrbits_ = flagSatellitesOrbits;
    setFlagPlanetsOrbits(false);
    setFlagSatellitesOrbits(false);

	if (obj.getType() == OBJECT_BODY){
		selected = obj;
		if (flagHints && flagIsolateSelected)
        	selected.as<Body>()->setFlagHints(!selected.as<Body>()->getFlagHints());
    } else {
		selected = Object();
	}
	// Undraw other objects hints, orbit, trails etc..
	//setFlagOrbits(flagTrails);
	setFlagPlanetsOrbits(flagPlanetsOrbits_);
	setFlagSatellitesOrbits(flagSatellitesOrbits_);
	setFlagTrails(flagTrails);  // TODO should just hide trail display and not affect data collection
}

void SolarSystemSelected::setFlagTrails(bool b)
{
	flagTrails = b;

	if (!b || !selected || (selected == ssystem->getCenterObject().get())) {
        for (auto &v : *ssystem) {
			v.second.body->setFlagTrail(b);
		}
	} else {
		// if a Body is selected and trails are on, fade out non-selected ones
        for (auto &v : *ssystem) {
			if ((selected == v.second.body.get()) || (selected == v.second.body->getParent()))
				v.second.body->setFlagTrail(b);
			else
                v.second.body->setFlagTrail(false);
		}
	}
}

void SolarSystemSelected::setFlagIsolateSelected(bool b)
{
	flagIsolateSelected = b;

	if (b) {
		if (auto body = selected.as<Body>())
            body->setFlagHints(true);
		for (auto &v : *ssystem)
			v.second.body->setFlagHints(false);
	} else
		setFlagHints(flagHints);
}

void SolarSystemSelected::setFlagHints(bool b)
{
	flagHints = b;

	if (flagIsolateSelected && b) {
		if (auto body = selected.as<Body>())
            body->setFlagHints(true);
		for (auto &v : *ssystem)
			v.second.body->setFlagHints(false);
	} else {
        for (auto &v : *ssystem)
			v.second.body->setFlagHints(b);
    }
}

void SolarSystemSelected::setFlagPlanetsOrbits(const std::string &_name, bool b)
{
    if (auto body = ssystem->searchByEnglishName(_name))
        body->setFlagOrbit(b);
}

void SolarSystemSelected::setFlagPlanetsOrbits(bool b)
{
    if (!(flagPlanetsOrbits | b)) // Avoid extra work when nothing to do
        return;

    auto body = selected.as<Body>();
	flagPlanetsOrbits = b;

    if (!body || body == ssystem->getCenterObject().get()) {
        for (auto &v : *ssystem) {
            if (!v.second.body->isSatellite())
                v.second.body->setFlagOrbit(b);
        }
    } else {
        body->setFlagOrbit(b);
    }

	// if (!b || !selected || selected == Object(ssystem->getCenterObject().get())) {
    //     for (auto &v : *ssystem) {
	// 		//if (v.second.body->get_parent() && v.second.body->getParent()->getEnglishName() =="Sun")
	// 		if (v.second.body->getTurnAround() == tACenter)
	// 			v.second.body->setFlagOrbit(b);
	// 	}
	// } else {
	// 	// if a Body is selected and orbits are on,
	// 	// fade out non-selected ones
	// 	// unless they are orbiting the selected Body 20080612 DIGITALIS
    //     for (auto &v : *ssystem) {
	// 		if (!v.second.body->isSatellite()) {
	// 			//if ((selected == v.second.body.get()) && (v.second.body->getParent()->getEnglishName() =="Sun")){
	// 			if ((selected == v.second.body.get()) && (v.second.body->getTurnAround() == tACenter)) {
	// 				v.second.body->setFlagOrbit(true);
	// 			}
	// 			else {
	// 				v.second.body->setFlagOrbit(false);
	// 			}
	// 		}
	// 		else {
	// 			if (selected == v.second.body->getParent().get()) {
	// 				v.second.body->setFlagOrbit(true);
	// 			}
	// 			else{
	// 				v.second.body->setFlagOrbit(false);
	// 			}
	// 		}
	// 	}
	// }
}

void SolarSystemSelected::setFlagSatellitesOrbits(bool b)
{
    if (!(flagSatellitesOrbits | b)) // Avoid extra work when nothing to do
        return;

    auto body = selected.as<Body>();
	flagSatellitesOrbits = b;

    if (!body || body == ssystem->getCenterObject().get()) {
        for (auto &v : *ssystem) {
            if (v.second.body->isSatellite())
                v.second.body->setFlagOrbit(b);
        }
    } else {
        for (auto &s : body->getSatellites())
            s->setFlagOrbit(b);
    }

	// if (!b || !selected || selected == Object(ssystem->getCenterObject().get())) {
    //     for (auto &v : *ssystem) {
	// 		//if (v.second.body->get_parent() && v.second.body->getParent()->getEnglishName() !="Sun"){
	// 		if (v.second.body->getTurnAround() == tABody) {
	// 			v.second.body->setFlagOrbit(b);
	// 		}
	// 	}
	// }
	// else {
	// 	// if the mother Body is selected orbits are on, else orbits are off
    //     for (auto &v : *ssystem) {
	// 		if (v.second.body->isSatellite()) {
	// 			if (v.second.body->get_parent()->getEnglishName() == selected.getEnglishName() || v.first == selected.getEnglishName()) {
	// 				v.second.body->setFlagOrbit(true);
	// 			}
	// 			else{
	// 				v.second.body->setFlagOrbit(false);
	// 			}
	// 		}
	// 	}
	// }
}

bool SolarSystemSelected::getFlag(BODY_FLAG name)
{
	switch (name) {
		case BODY_FLAG::F_TRAIL: return flagTrails; break;
		case BODY_FLAG::F_HINTS: return flagHints; break;
		case BODY_FLAG::F_ORBIT : return (flagPlanetsOrbits||flagSatellitesOrbits); break;
		default: break;
	}
	return false;
}

void SolarSystemSelected::setSelected(const std::string& englishName) {
		setSelected(ssystem->searchByEnglishName(englishName).get());
}
