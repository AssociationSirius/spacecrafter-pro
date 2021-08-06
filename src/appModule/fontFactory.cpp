/*
 * Copyright (C) 2020 of the LSS Team & Association Sirius
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
 * Spacecrafter is a free open project of the LSS team
 * See the TRADEMARKS file for free open project usage requirements.
 *
 */

#include "appModule/fontFactory.hpp"
#include "tools/init_parser.hpp"
#include "tools/app_settings.hpp"
#include "tools/log.hpp"
#include "tools/utility.hpp"
#include "mainModule/define_key.hpp"
#include "interfaceModule/base_command_interface.hpp"

FontFactory::FontFactory(int _resolution)
{
	setStrToTarget();
	m_resolution = _resolution;
}

void FontFactory::setStrToTarget()
{
    m_strToTarget[TF_TEXT] = TARGETFONT::CF_TEXTS;
	m_strToTarget[TF_PLANETS] = TARGETFONT::CF_PLANETS;
	m_strToTarget[TF_CONSTELLATIONS] = TARGETFONT::CF_CONSTELLATIONS;
	m_strToTarget[TF_CARDINAL] = TARGETFONT::CF_CARDINALS;
	m_strToTarget[TF_STARS] = TARGETFONT::CF_HIPSTARS;
	m_strToTarget[TF_MENU] = TARGETFONT::CF_MENU;
	m_strToTarget[TF_GENERAL] = TARGETFONT::CF_GENERAL;
}


FontFactory::~FontFactory()
{
	tuiFont.release();
}

void FontFactory::buildAllFont()
{
	std::cout << "debut construction des fonts" << std::endl;
	tuiFont = std::make_unique<s_font>(FontSizeTuiMenu, FontNameTuiMenu);
	tuiFont->rebuild(FontSizeTuiMenu, FontNameTuiMenu);
	tuiFont->rebuild(FontSizeTuiMenu+2, FontNameTuiMenu);
	std::cout << "fin construction des fonts" << std::endl;
}

void FontFactory::init(const InitParser& conf)
{
	FontFileNameGeneral = AppSettings::Instance()->getUserFontDir()+conf.getStr(SCS_FONT, SCK_FONT_GENERAL_NAME);
	FontFileNamePlanet = AppSettings::Instance()->getUserFontDir()+conf.getStr(SCS_FONT, SCK_FONT_PLANET_NAME);
	FontFileNameConstellation = AppSettings::Instance()->getUserFontDir()+conf.getStr(SCS_FONT, SCK_FONT_CONSTELLATION_NAME);

	FontFileNameText =  AppSettings::Instance()->getUserFontDir()+conf.getStr(SCS_FONT, SCK_FONT_TEXT_NAME);

	FontNameTuiMenu = AppSettings::Instance()->getUserFontDir()+conf.getStr(SCS_FONT, SCK_FONT_MENU_NAME);

	FontSizeGeneral = conf.getDouble (SCS_FONT,SCK_FONT_GENERAL_SIZE);
	FontSizeConstellation = conf.getDouble(SCS_FONT,SCK_FONT_CONSTELLATION_SIZE);
	FontSizePlanet = conf.getDouble(SCS_FONT,SCK_FONT_PLANET_SIZE);
	FontSizeCardinalPoints = conf.getDouble(SCS_FONT,SCK_FONT_CARDINALPOINTS_SIZE);

    FontSizeText =  conf.getDouble(SCS_FONT, SCK_FONT_TEXT_SIZE);

	FontSizeTuiMenu   = conf.getDouble (SCS_FONT, SCK_FONT_MENUTUI_SIZE);

	m_fontResolution = conf.getDouble(SCS_FONT, SCK_FONT_RESOLUTION_SIZE);
    if (m_fontResolution <1.0)
        m_fontResolution = 1024.0;

    // mise à l'échelle des FontSize
    FontSizeText = round(FontSizeText * m_resolution / m_fontResolution) ;
    FontSizeGeneral = round(FontSizeGeneral * m_resolution / m_fontResolution) ;
    FontSizeConstellation = round(FontSizeConstellation * m_resolution / m_fontResolution) ;
    FontSizePlanet = round(FontSizePlanet * m_resolution / m_fontResolution) ;
    FontSizeCardinalPoints = round(FontSizeCardinalPoints * m_resolution / m_fontResolution) ;
	FontSizeTuiMenu = round(FontSizeTuiMenu * m_resolution / m_fontResolution) ;
}


void FontFactory::updateFont(const std::string& targetName, const std::string& fontName, const std::string& sizeValue)
{
	// gestion de la taille
	double size = Utility::strToDouble(sizeValue) * m_resolution / m_fontResolution;

	//gestion du module
	auto const it = m_strToTarget.find(targetName);
	if (it == m_strToTarget.end()) {
		cLog::get()->write("Unknown FontFactory target "+targetName, LOG_TYPE::L_WARNING);
		return;
	}

	switch(it->second) {
		// Media
		case TARGETFONT::CF_TEXTS :
			// text_usr->setFont(size==0 ? FontSizeText : size, fontName );
			break;
		// Core
		case TARGETFONT::CF_PLANETS :
			// ssystem->setFont(size==0 ? FontSizePlanet : size, fontName );
			break;
		case TARGETFONT::CF_CONSTELLATIONS :
			// asterisms->setFont(size==0 ? FontSizeConstellation : size, fontName );
			break;
		case TARGETFONT::CF_CARDINALS :
			// cardinals_points->setFont(size==0 ? FontSizeCardinalPoints : size, fontName );
			break;
		case TARGETFONT::CF_HIPSTARS :
			// hip_stars->setFont(size==0 ? FontSizeGeneral : size, fontName );
			break;
		case TARGETFONT::CF_MENU:
			break;
		case TARGETFONT::CF_GENERAL:
			break;
		case TARGETFONT::CF_NONE:
			break;
	}
}