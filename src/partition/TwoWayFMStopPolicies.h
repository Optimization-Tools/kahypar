#ifndef PARTITION_TWOWAYFMSTOPPOLICIES_H_
#define PARTITION_TWOWAYFMSTOPPOLICIES_H_

namespace partition {

struct NumberOfFruitlessMovesStopsSearch {
  template <typename Configuration>
  static bool searchShouldStop(int min_cut_index, int current_index, const Configuration& config) {
    return current_index - min_cut_index > config.two_way_fm.max_number_of_fruitless_moves;
  }
  
  static void resetStatistics() { }
  
  template <typename Gain>
  static void updateStatistics(Gain) { }
  
 protected:
  ~NumberOfFruitlessMovesStopsSearch() {}
};

struct RandomWalkModelStopsSearch {
  
  template <typename Configuration>
   static bool searchShouldStop(int, int, const Configuration& config) {
    //PRINT(_num_steps << "*" << _expected_gain << "^2=" << _num_steps * _expected_gain * _expected_gain);
    //PRINT(config.two_way_fm.alpha << "*" << _expected_variance << "+" << config.two_way_fm.beta << "="
    //      << config.two_way_fm.alpha * _expected_variance + config.two_way_fm.beta);
    return _num_steps * _expected_gain * _expected_gain >
        config.two_way_fm.alpha * _expected_variance + config.two_way_fm.beta;
  }

  static void resetStatistics() {
    _num_steps = 0;
    _expected_gain = 0.0;
    _expected_variance = 0.0;
    _sum_gains = 0.0;
    _sum_gains_squared = 0.0;
  }
  
  template <typename Gain>
  static void updateStatistics(Gain gain) {
    ++_num_steps;
    _sum_gains += gain;
    _sum_gains_squared += gain * gain;
    _expected_gain = _sum_gains / _num_steps;
    // http://de.wikipedia.org/wiki/Standardabweichung#Berechnung_f.C3.BCr_auflaufende_Messwerte
    if (_num_steps > 1) {
      _expected_variance =(_sum_gains_squared-((_sum_gains*_sum_gains)/_num_steps))/(_num_steps-1);
    } else {
      _expected_variance = 0.0;
    }
  }
  
 private:
  static int _num_steps;
  static double _expected_gain;
  static double _expected_variance;
  static double _sum_gains;
  static double _sum_gains_squared;
 protected:
  ~RandomWalkModelStopsSearch() {}
};

int RandomWalkModelStopsSearch::_num_steps = 0;
double RandomWalkModelStopsSearch::_sum_gains = 0.0;
double RandomWalkModelStopsSearch::_sum_gains_squared = 0.0;
double RandomWalkModelStopsSearch::_expected_gain = 0.0;
double RandomWalkModelStopsSearch::_expected_variance = 0.0;

} // namespace partition

#endif  // PARTITION_TWOWAYFMSTOPPOLICIES_H_
