#include <fstream>
#include <iostream>
#include <vector>

#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include <boost/geometry/algorithms/simplify.hpp>
#include <boost/geometry/strategies/spherical/distance_cross_track.hpp>
#include <boost/geometry/strategies/agnostic/simplify_douglas_peucker.hpp>
#include <boost/geometry.hpp>

namespace bg = boost::geometry;
using tokenizer = boost::tokenizer<boost::char_separator<char>>;
using point_t = bg::model::point<double, 2, bg::cs::geographic<bg::degree>>;
using polyline_t = bg::model::linestring<point_t>;

template<typename RadiusTypeOrSphere = double, typename CalculationType = void>
class haversine_donut : public bg::strategy::distance::haversine<RadiusTypeOrSphere, CalculationType> {
  public:
  inline haversine_donut(): bg::strategy::distance::haversine<RadiusTypeOrSphere, CalculationType>(6378140.0) {}
};

auto readFile() {
  polyline_t coordinates{};

  std::fstream coordinateFile;
  boost::char_separator<char> sep{","};
  coordinateFile.open("coordinates.csv", std::ios::in);
  if(coordinateFile.is_open()) {
    std::string line;
    while(getline(coordinateFile, line)) {
      tokenizer tok{line, sep};
      std::vector<std::string> vars {tok.begin(), tok.end()};
      point_t coord{boost::lexical_cast<double>(vars[0]), boost::lexical_cast<double>(vars[1])};
      bg::append(coordinates, coord);
    }
  }
  coordinateFile.close();
  return coordinates;
}

double ConvertToEarthRadiusProportion(const double distance) {
  constexpr double earth_radius = 6378140.0;
  return distance/earth_radius;
}

int main(int /*argc*/, char **/*argv[]*/) {
  std::cout << "Douglas Peucker simplification algorithm application using Boost::Geometry" << std::endl;
  polyline_t polyline = readFile();
  polyline_t decimated_polyline{};
  bg::strategy::simplify::douglas_peucker<point_t, bg::strategy::distance::cross_track<double>> douglas_peucker;
  bg::simplify(polyline, decimated_polyline, ConvertToEarthRadiusProportion(100.0), douglas_peucker);
  std::cout << "Original Polyline Data Points: " << polyline.size() <<std::endl;
  std::cout << "After bg::simplify applied: " << decimated_polyline.size() <<std::endl;
  return 0;
}