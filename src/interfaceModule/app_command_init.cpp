#include "interfaceModule/app_command_init.hpp"
#include <vector>
#include "tools/log.hpp"

AppCommandInit::AppCommandInit()
{}

AppCommandInit::~AppCommandInit()
{}

void AppCommandInit::initialiseCommandsName(std::map<const std::string, SC_COMMAND> &m_commands)
{
	m_commands["add"] = SC_COMMAND::SC_ADD;
	m_commands["audio"] = SC_COMMAND::SC_AUDIO;
	m_commands["body_trace"] = SC_COMMAND::SC_BODY_TRACE;
	m_commands["audio"] = SC_COMMAND::SC_AUDIO;
	m_commands["body"] = SC_COMMAND::SC_BODY;

	m_commands["camera"] = SC_COMMAND::SC_CAMERA;
	m_commands["flyto"] = SC_COMMAND::SC_CAMERA; //alias de camera

	m_commands["clear"] = SC_COMMAND::SC_CLEAR;
	m_commands["color"] = SC_COMMAND::SC_COLOR;
	m_commands["configuration"] = SC_COMMAND::SC_CONFIGURATION;
	m_commands["constellation"] = SC_COMMAND::SC_CONSTELLATION;
	m_commands["date"] = SC_COMMAND::SC_DATE;
	m_commands["define"] = SC_COMMAND::SC_DEFINE;

	m_commands["deselect"] = SC_COMMAND::SC_DESELECT;
	m_commands["domemasters"] = SC_COMMAND::SC_DOMEMASTERS;
	m_commands["dso"] = SC_COMMAND::SC_DSO;
	//m_commands["external_mplayer"] = SC_COMMAND::SC_EXERNASC_MPLAYER;
	m_commands["external_viewer"] = SC_COMMAND::SC_EXTERNASC_VIEWER;

	m_commands["flag"] = SC_COMMAND::SC_FLAG;
	m_commands["get"] = SC_COMMAND::SC_GET;
	m_commands["illuminate"] = SC_COMMAND::SC_ILLUMINATE;
	m_commands["image"] = SC_COMMAND::SC_IMAGE;
	m_commands["landscape"] = SC_COMMAND::SC_LANDSCAPE;

	m_commands["look_at"] = SC_COMMAND::SC_LOOK;
	m_commands["media"] = SC_COMMAND::SC_MEDIA;
	m_commands["meteors"] = SC_COMMAND::SC_METEORS;
	m_commands["moveto"] = SC_COMMAND::SC_MOVETO;
	m_commands["movetocity"] = SC_COMMAND::SC_MOVETOCITY;

	m_commands["multiply"] = SC_COMMAND::SC_MULTIPLY;
	m_commands["personal"] = SC_COMMAND::SC_PERSONAL;
	m_commands["personeq"] = SC_COMMAND::SC_PERSONEQ;
	m_commands["planet_scale"] = SC_COMMAND::SC_PLANET_SCALE;

	m_commands["position"] = SC_COMMAND::SC_POSITION;
	m_commands["print"] = SC_COMMAND::SC_PRINT;
	m_commands["random"] = SC_COMMAND::SC_RANDOM;
	m_commands["script"] = SC_COMMAND::SC_SCRIPT;
	m_commands["search"] = SC_COMMAND::SC_SEARCH;

	m_commands["select"] = SC_COMMAND::SC_SELECT;
	m_commands["set"] = SC_COMMAND::SC_SET;
	m_commands["shutdown"] = SC_COMMAND::SC_SHUTDOWN;
	m_commands["sky_culture"] = SC_COMMAND::SC_SKY_CULTURE;

	m_commands["star_lines"] = SC_COMMAND::SC_STAR_LINES;
	m_commands["struct"] = SC_COMMAND::SC_STRUCT;
	m_commands["suntrace"] = SC_COMMAND::SC_SUNTRACE;
	m_commands["text"] = SC_COMMAND::SC_TEXT;
	m_commands["timerate"] = SC_COMMAND::SC_TIMERATE;

	m_commands["wait"] = SC_COMMAND::SC_WAIT;
	m_commands["zoom"] = SC_COMMAND::SC_ZOOMR;

	//make a copy to futur exploitation
	for (const auto& i : m_commands) {
		commandList.push_back(i.first);
	}
}

void AppCommandInit::initialiseFlagsName(std::map<const std::string, FLAG_NAMES> &m_flags)
{
	m_flags["antialias_lines"] = FLAG_NAMES::FN_ANTIALIAS_LINES;
	m_flags["constellation_drawing"] = FLAG_NAMES::FN_CONSTELLATION_DRAWING;
	m_flags["constellation_names"] = FLAG_NAMES::FN_CONSTELLATION_NAMES;
	m_flags["constellation_art"] = FLAG_NAMES::FN_CONSTELLATION_ART;
	m_flags["constellation_boundaries"] = FLAG_NAMES::FN_CONSTELLATION_BOUNDARIES;
	m_flags["constellation_pick"] = FLAG_NAMES::FN_CONSTELLATION_PICK;

	m_flags["star_twinkle"] = FLAG_NAMES::FN_STAR_TWINKLE;
	m_flags["navigation"] = FLAG_NAMES::FN_NAVIGATION;
	m_flags["show_tui_datetime"] = FLAG_NAMES::FN_SHOW_TUI_DATETIME;
	m_flags["show_tui_short_obj_info"] = FLAG_NAMES::FN_SHOW_TUI_SHORT_OBJ_INFO;
	m_flags["manual_zoom"] = FLAG_NAMES::FN_MANUAL_ZOOM;

	m_flags["light_travel_time"] = FLAG_NAMES::FN_LIGHT_TRAVEL_TIME;
	m_flags["fog"] = FLAG_NAMES::FN_FOG;
	m_flags["atmosphere"] = FLAG_NAMES::FN_ATMOSPHERE;
	m_flags["azimuthal_grid"] = FLAG_NAMES::FN_AZIMUTHAL_GRID;
	m_flags["equatorial_grid"] = FLAG_NAMES::FN_EQUATORIAL_GRID;

	m_flags["ecliptic_grid"] = FLAG_NAMES::FN_ECLIPTIC_GRID;
	m_flags["galactic_grid"] = FLAG_NAMES::FN_GALACTIC_GRID;
	m_flags["equator_line"] = FLAG_NAMES::FN_EQUATOR_LINE;
	m_flags["galactic_line"] = FLAG_NAMES::FN_GALACTIC_LINE;
	m_flags["ecliptic_line"] = FLAG_NAMES::FN_ECLIPTIC_LINE;

	m_flags["precession_circle"] = FLAG_NAMES::FN_PRECESSION_CIRCLE;
	m_flags["circumpolar_circle"] = FLAG_NAMES::FN_CIRCUMPOLAR_CIRCLE;
	m_flags["tropic_lines"] = FLAG_NAMES::FN_TROPIC_LINES;
	m_flags["meridian_line"] = FLAG_NAMES::FN_MERIDIAN_LINE;
	m_flags["zenith_line"] = FLAG_NAMES::FN_ZENITH_LINE;

	m_flags["polar_circle"] = FLAG_NAMES::FN_POLAR_CIRCLE;
	m_flags["polar_point"] = FLAG_NAMES::FN_POLAR_POINT;
	m_flags["ecliptic_center"] = FLAG_NAMES::FN_ECLIPTIC_CENTER;
	m_flags["galactic_pole"] = FLAG_NAMES::FN_GALACTIC_POLE;
	m_flags["galactic_center"] = FLAG_NAMES::FN_GALACTIC_CENTER;
	m_flags["vernal_points"] = FLAG_NAMES::FN_VERNAL_POINTS;

	m_flags["analemma_line"] = FLAG_NAMES::FN_ANALEMMA_LINE;
	m_flags["analemma"] = FLAG_NAMES::FN_ANALEMMA;
	m_flags["aries_line"] = FLAG_NAMES::FN_ARIES_LINE;
	m_flags["zodiac"] = FLAG_NAMES::FN_ZODIAC;

	m_flags["personal"] = FLAG_NAMES::FN_PERSONAL;
	m_flags["personeq"] = FLAG_NAMES::FN_PERSONEQ;
	m_flags["nautical_alt"] = FLAG_NAMES::FN_NAUTICAL;
	m_flags["nautical_ra"] = FLAG_NAMES::FN_NAUTICEQ;
	m_flags["object_coordinates"] = FLAG_NAMES::FN_OBJCOORD;
	m_flags["mouse_coordinates"] = FLAG_NAMES::FN_MOUSECOORD;
	m_flags["angular_distance"] = FLAG_NAMES::FN_ANG_DIST;
	m_flags["loxodromy"] = FLAG_NAMES::FN_LOXODROMY;
	m_flags["orthodromy"] = FLAG_NAMES::FN_ORTHODROMY;

	m_flags["greenwich_line"] = FLAG_NAMES::FN_GREENWICH_LINE;
	m_flags["vertical_line"] = FLAG_NAMES::FN_VERTICAL_LINE;
	m_flags["cardinal_points"] = FLAG_NAMES::FN_CARDINAL_POINTS;
	m_flags["clouds"] = FLAG_NAMES::FN_CLOUDS;

	m_flags["moon_scaled"] = FLAG_NAMES::FN_MOON_SCALED;
	m_flags["sun_scaled"] = FLAG_NAMES::FN_SUN_SCALED;
	m_flags["landscape"] = FLAG_NAMES::FN_LANDSCAPE;
	m_flags["stars"] = FLAG_NAMES::FN_STARS;
	m_flags["star_names"] = FLAG_NAMES::FN_STAR_NAMES;
	m_flags["star_pick"] = FLAG_NAMES::FN_STAR_PICK;
	m_flags["atmospheric_refraction"] = FLAG_NAMES::FN_ATMOSPHERIC_REFRACTION;

	m_flags["planets"] = FLAG_NAMES::FN_PLANETS;
	m_flags["planet_names"] = FLAG_NAMES::FN_PLANET_NAMES;
	m_flags["planet_orbits"] = FLAG_NAMES::FN_PLANET_ORBITS;
	m_flags["orbits"] = FLAG_NAMES::FN_ORBITS;
	m_flags["planets_orbits"] = FLAG_NAMES::FN_PLANETS_ORBITS;

	m_flags["planets_axis"] = FLAG_NAMES::FN_PLANETS_AXIS;
	m_flags["satellites_orbits"] = FLAG_NAMES::FN_SATELLITES_ORBITS;
	m_flags["nebulae"] = FLAG_NAMES::FN_NEBULAE;
	m_flags["nebula_names"] = FLAG_NAMES::FN_NEBULA_NAMES;
	m_flags["nebula_hints"] = FLAG_NAMES::FN_NEBULA_HINTS;

	m_flags["milky_way"] = FLAG_NAMES::FN_MILKY_WAY;
	m_flags["bright_nebulae"] = FLAG_NAMES::FN_BRIGHT_NEBULAE;
	m_flags["object_trails"] = FLAG_NAMES::FN_OBJECT_TRAILS;
	m_flags["track_object"] = FLAG_NAMES::FN_TRACK_OBJECT;
	m_flags["script_gui_debug"] = FLAG_NAMES::FN_SCRIPT_GUI_DEBUG;

	m_flags["lock_sky_position"] = FLAG_NAMES::FN_LOCK_SKY_POSITION;
	m_flags["body_trace"] = FLAG_NAMES::FN_BODY_TRACE;
	m_flags["show_latlon"] = FLAG_NAMES::FN_SHOW_LATLON;
	m_flags["color_inverse"] = FLAG_NAMES::FN_COLOR_INVERSE;
	m_flags["oort"] = FLAG_NAMES::FN_OORT;

	m_flags["stars_trace"] = FLAG_NAMES::FN_STARS_TRACE;
	m_flags["star_lines"] = FLAG_NAMES::FN_STAR_LINES;
	m_flags["sky_draw"] = FLAG_NAMES::FN_SKY_DRAW;
	m_flags["dso_pictograms"] = FLAG_NAMES::FN_DSO_PICTOGRAMS;
	m_flags["zodiacal_light"] = FLAG_NAMES::FN_ZODIAC_LIGHT;

	m_flags["tully"] = FLAG_NAMES::FN_TULLY;
	m_flags["satellites"] = FLAG_NAMES::FN_SATELLITES;

	//make a copy to futur exploitation
	for (const auto& i : m_flags) {
		flagList.push_back(i.first);
	}
}

void AppCommandInit::initialiseColorCommand(std::map<const std::string, COLORCOMMAND_NAMES> &m_color)
{
	m_color["constellation_lines"] = COLORCOMMAND_NAMES::CC_CONSTELLATION_LINES;
	m_color["constellation_names"] = COLORCOMMAND_NAMES::CC_CONSTELLATION_NAMES;
	m_color["constellation_art"] = COLORCOMMAND_NAMES::CC_CONSTELLATION_ART;
	m_color["constellation_boundaries"] = COLORCOMMAND_NAMES::CC_CONSTELLATION_BOUNDARIES;
	m_color["cardinal_points"] = COLORCOMMAND_NAMES::CC_CARDINAL_POINTS;
	m_color["planet_orbits"] = COLORCOMMAND_NAMES::CC_PLANET_ORBITS;

	m_color["planet_names"] = COLORCOMMAND_NAMES::CC_PLANET_NAMES;
	m_color["planet_trails"] = COLORCOMMAND_NAMES::CC_PLANET_TRAILS;
	m_color["azimuthal_grid"] = COLORCOMMAND_NAMES::CC_AZIMUTHAL_GRID;
	m_color["equator_grid"] = COLORCOMMAND_NAMES::CC_EQUATOR_GRID;
	m_color["ecliptic_grid"] = COLORCOMMAND_NAMES::CC_ECLIPTIC_GRID;
	m_color["galactic_grid"] = COLORCOMMAND_NAMES::CC_GALACTIC_GRID;

	m_color["galactic_grid"] = COLORCOMMAND_NAMES::CC_EQUATOR_LINE;
	m_color["galactic_line"] = COLORCOMMAND_NAMES::CC_GALACTIC_LINE;
	m_color["ecliptic_line"] = COLORCOMMAND_NAMES::CC_ECLIPTIC_LINE;
	m_color["meridian_line"] = COLORCOMMAND_NAMES::CC_MERIDIAN_LINE;
	m_color["zenith_line"] = COLORCOMMAND_NAMES::CC_ZENITH_LINE;
	m_color["polar_point"] = COLORCOMMAND_NAMES::CC_POLAR_POINT;

	m_color["polar_circle"] = COLORCOMMAND_NAMES::CC_POLAR_CIRCLE;
	m_color["ecliptic_center"] = COLORCOMMAND_NAMES::CC_ECLIPTIC_CENTER;
	m_color["galactic_pole"] = COLORCOMMAND_NAMES::CC_GALACTIC_POLE;
	m_color["galactic_center"] = COLORCOMMAND_NAMES::CC_GALACTIC_CENTER;
	m_color["vernal_points"] = COLORCOMMAND_NAMES::CC_VERNAL_POINTS;
	m_color["analemma"] = COLORCOMMAND_NAMES::CC_ANALEMMA;

	m_color["analemma_line"] = COLORCOMMAND_NAMES::CC_ANALEMMA_LINE;
	m_color["greenwich_line"] = COLORCOMMAND_NAMES::CC_GREENWICH_LINE;
	m_color["aries_line"] = COLORCOMMAND_NAMES::CC_ARIES_LINE;
	m_color["zodiac"] = COLORCOMMAND_NAMES::CC_ZODIAC;
	m_color["personal"] = COLORCOMMAND_NAMES::CC_PERSONAL;
	m_color["personeq"] = COLORCOMMAND_NAMES::CC_PERSONEQ;

	m_color["nautical_alt"] = COLORCOMMAND_NAMES::CC_NAUTICAL_ALT;
	m_color["nautical_ra"] = COLORCOMMAND_NAMES::CC_NAUTICAL_RA;
	m_color["object_coordinates"] = COLORCOMMAND_NAMES::CC_OBJECT_COORDINATES;
	m_color["mouse_coordinates"] = COLORCOMMAND_NAMES::CC_MOUSE_COORDINATES;
	m_color["angular_distance"] = COLORCOMMAND_NAMES::CC_ANGULAR_DISTANCE;
	m_color["loxodromy"] = COLORCOMMAND_NAMES::CC_LOXODROMY;

	m_color["orthodromy"] = COLORCOMMAND_NAMES::CC_ORTHODROMY;
	m_color["vertical_line"] = COLORCOMMAND_NAMES::CC_VERTICAL_LINE;
	m_color["nebula_names"] = COLORCOMMAND_NAMES::CC_NEBULA_NAMES;
	m_color["nebula_circle"] = COLORCOMMAND_NAMES::CC_NEBULA_CIRCLE;
	m_color["precession_circle"] = COLORCOMMAND_NAMES::CC_PRECESSION_CIRCLE;
	m_color["text_usr_color"] = COLORCOMMAND_NAMES::CC_TEXT_USR_COLOR;

	m_color["star_table"] = COLORCOMMAND_NAMES::CC_STAR_TABLE;

	//make a copy to futur exploitation
	for (const auto& i : m_color) {
		colorList.push_back(i.first);
	}
}

void AppCommandInit::initialiseSetCommand(std::map<const std::string, SCD_NAMES> &m_appcommand)
{
	m_appcommand["atmosphere_fade_duration"] = SCD_NAMES::APP_ATMOSPHERE_FADE_DURATION;
	m_appcommand["auto_move_duration"] = SCD_NAMES::APP_AUTO_MOVE_DURATION;
	m_appcommand["constellation_art_fade_duration"] = SCD_NAMES::APP_CONSTELLATION_ART_FADE_DURATION;
	m_appcommand["constellation_art_intensity"] = SCD_NAMES::APP_CONSTELLATION_ART_INTENSITY;
	m_appcommand["light_pollution_limiting_magnitude"] = SCD_NAMES::APP_LIGHT_POLLUTION_LIMITING_MAGNITUDE;

	m_appcommand["heading"] = SCD_NAMES::APP_HEADING;
	m_appcommand["home_planet"] = SCD_NAMES::APP_HOME_PLANET;
	m_appcommand["landscape_name"] = SCD_NAMES::APP_LANDSCAPE_NAME;
	m_appcommand["line_width"] = SCD_NAMES::APP_LINE_WIDTH;
	m_appcommand["max_mag_nebula_name"] = SCD_NAMES::APP_MAX_MAG_NEBULA_NAME;
	m_appcommand["max_mag_star_name"] = SCD_NAMES::APP_MAX_MAG_STAR_NAME;

	m_appcommand["moon_scale"] = SCD_NAMES::APP_MOON_SCALE;
	m_appcommand["sun_scale"] = SCD_NAMES::APP_SUN_SCALE;
	m_appcommand["milky_way_texture"] = SCD_NAMES::APP_MILKY_WAY_TEXTURE;
	m_appcommand["sky_culture"] = SCD_NAMES::APP_SKY_CULTURE;
	m_appcommand["sky_locale"] = SCD_NAMES::APP_SKY_LOCALE;
	m_appcommand["ui_locale"] = SCD_NAMES::APP_UI_LOCALE;

	m_appcommand["star_mag_scale"] = SCD_NAMES::APP_STAR_MAG_SCALE;
	m_appcommand["star_size_limit"] = SCD_NAMES::APP_STAR_SIZE_LIMIT;
	m_appcommand["planet_size_limit"] = SCD_NAMES::APP_PLANET_SIZE_LIMIT;
	m_appcommand["star_scale"] = SCD_NAMES::APP_STAR_SCALE;
	m_appcommand["star_twinkle_amount"] = SCD_NAMES::APP_STAR_TWINKLE_AMOUNT;
	m_appcommand["star_fader_duration"] = SCD_NAMES::APP_STAR_FADER_DURATION;

	m_appcommand["star_limiting_mag"] = SCD_NAMES::APP_STAR_LIMITING_MAG;
	m_appcommand["time_zone"] = SCD_NAMES::APP_TIME_ZONE;
	m_appcommand["ambient_light"] = SCD_NAMES::APP_AMBIENT_LIGHT;
	m_appcommand["text_fading_duration"] = SCD_NAMES::APP_TEXT_FADING_DURATION;
	m_appcommand["milky_way_fader_duration"] = SCD_NAMES::APP_MILKY_WAY_FADER_DURATION;
	m_appcommand["milky_way_intensity"] = SCD_NAMES::APP_MILKY_WAY_INTENSITY;

	m_appcommand["zoom_offset"] = SCD_NAMES::APP_ZOOM_OFFSET;
	m_appcommand["startup_time_mode"] = SCD_NAMES::APP_STARTUP_TIME_MODE;
	m_appcommand["date_display_format"] = SCD_NAMES::APP_DATE_DISPLAY_FORMAT;
	m_appcommand["time_display_format"] = SCD_NAMES::APP_TIME_DISPLAY_FORMAT;
	m_appcommand["mode"] = SCD_NAMES::APP_MODE;
	m_appcommand["screen_fader"] = SCD_NAMES::APP_SCREEN_FADER;

	m_appcommand["stall_radius_unit"] = SCD_NAMES::APP_STALL_RADIUS_UNIT;
	m_appcommand["tully_color_mode"] = SCD_NAMES::APP_TULLY_COLOR_MODE;
	m_appcommand["datetime_display_position"] = SCD_NAMES::APP_DATETIME_DISPLAY_POSITION;
	m_appcommand["datetime_display_number"] = SCD_NAMES::APP_DATETIME_DISPLAY_NUMBER;

	//make a copy to futur exploitation
	for (const auto& i : m_appcommand) {
		setList.push_back(i.first);
	}
}

template<typename T> typename T::size_type LevensteinDistance(const T &source, const T &target)
{
    if (source.size() > target.size()) {
        return LevensteinDistance(target, source);
    }

    using TSizeType = typename T::size_type;
    const TSizeType min_size = source.size(), max_size = target.size();
    std::vector<TSizeType> lev_dist(min_size + 1);

    for (TSizeType i = 0; i <= min_size; ++i) {
        lev_dist[i] = i;
    }

    for (TSizeType j = 1; j <= max_size; ++j) {
        TSizeType previous_diagonal = lev_dist[0], previous_diagonal_save;
        ++lev_dist[0];

        for (TSizeType i = 1; i <= min_size; ++i) {
            previous_diagonal_save = lev_dist[i];
            if (source[i - 1] == target[j - 1]) {
                lev_dist[i] = previous_diagonal;
            } else {
                lev_dist[i] = std::min(std::min(lev_dist[i - 1], lev_dist[i]), previous_diagonal) + 1;
            }
            previous_diagonal = previous_diagonal_save;
        }
    }
    return lev_dist[min_size];
}

void AppCommandInit::searchNeighbour(const std::string &source, const std::list<std::string> &target)
{
	int distance = 0;
	int minDistance = 99999;
	std::string solution;

	for(const auto &i : target) {
		distance = LevensteinDistance(source,i);
		if (distance < minDistance) {
			minDistance = distance;
			solution = i;
		}
	}
	std::string helpMsg = source + " is unknown. Did you mean "+ solution + " ?";
	cLog::get()->write( helpMsg,LOG_TYPE::L_DEBUG, LOG_FILE::SCRIPT );
	//std::cout << source << " a pour proche valeur " << solution << std::endl;
}
