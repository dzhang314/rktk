// C++ standard library headers
#include <cmath> // for std::isfinite
#include <cstdlib> // for std::exit
#include <cstring> // for std::strlen
#include <ctime> // for std::clock
#include <iostream> // for std::cout
#include <limits> // for std::numeric_limits

// RKTK headers
#include "OptimizerDriver.hpp"

typedef std::numeric_limits<float> float_limits;
typedef std::numeric_limits<double> double_limits;
typedef std::numeric_limits<long double> long_double_limits;

int get_precision(int argc, char **argv) {
    if (argc >= 2) {
        char *end;
        const long long int precision = std::strtoll(argv[1], &end, 10);
        const bool read_whole_arg = (std::strlen(argv[1]) ==
                                     static_cast<std::size_t>(end - argv[1]));
        const bool is_positive = (precision > 0);
        if (read_whole_arg && is_positive) {
            std::cout << "Requested " << precision << "-bit precision."
                      << std::endl;
            if (precision < float_limits::digits) {
                std::cout << "Rounding up to " << float_limits::digits
                          << "-bit precision, which is the smallest "
                             "available machine precision." << std::endl;
                return float_limits::digits;
            } else if (precision == float_limits::digits) {
                return float_limits::digits;
            } else if (precision < double_limits::digits) {
                std::cout << "Rounding up to " << double_limits::digits
                          << "-bit precision, which is the next "
                             "available machine precision." << std::endl;
                return double_limits::digits;
            } else if (precision == double_limits::digits) {
                return double_limits::digits;
            } else if (precision < long_double_limits::digits) {
                std::cout << "Rounding up to " << long_double_limits::digits
                          << "-bit precision, which is the next "
                             "available machine precision." << std::endl;
                return long_double_limits::digits;
            } else if (precision == long_double_limits::digits) {
                return long_double_limits::digits;
            } else {
                std::cout << "WARNING: Requested precision exceeds "
                             "available machine precision. Rounding down to "
                          << long_double_limits::digits
                          << "-bit precision, which is the highest "
                             "available machine precision." << std::endl;
                return long_double_limits::digits;
            }
        } else {
            std::cout << "WARNING: Could not interpret command-line argument "
                      << argv[1] << " as a positive integer. Defaulting to"
                                    " double (" << double_limits::digits
                      << "-bit) precision." << std::endl;
            return double_limits::digits;
        }
    } else {
        std::cout << "Defaulting to double (" << double_limits::digits
                  << "-bit) precision." << std::endl;
        return double_limits::digits;
    }
}

double get_print_period(int argc, char **argv) {
    if (argc >= 3) {
        char *end;
        const double print_period = std::strtod(argv[2], &end);
        const bool read_whole_arg = (std::strlen(argv[2]) ==
                                     static_cast<std::size_t>(end - argv[2]));
        const bool is_finite = std::isfinite(print_period);
        const bool is_positive = (print_period >= 0.0);
        if (read_whole_arg && is_finite && is_positive) {
            return print_period;
        }
    }
    return 0.5;
}

int get_print_precision(int argc, char **argv) {
    if (argc >= 4) {
        char *end;
        const long long print_precision = std::strtoll(argv[3], &end, 10);
        const bool read_whole_arg = (std::strlen(argv[3]) ==
                                     static_cast<std::size_t>(end - argv[3]));
        const bool is_non_negative = (print_precision >= 0);
        const bool in_range = (print_precision <=
                               std::numeric_limits<int>::max());
        if (read_whole_arg && is_non_negative && in_range) {
            return static_cast<int>(print_precision);
        }
    }
    return 0;
}

enum class SearchMode {
    EXPLORE, REFINE
};

template <typename T>
void run_main_loop(char **argv, SearchMode mode, int print_prec,
                   std::clock_t clocks_between_prints) {
    rktk::OptimizerDriver<T> optimizer;
    if (mode == SearchMode::REFINE) {
        optimizer.initialize_from_file(std::string(argv[4]));
    }
    std::clock_t last_print_clock;
    reset_d:
    if (mode == SearchMode::EXPLORE) { optimizer.initialize_random(); }
    optimizer.print(print_prec);
    optimizer.write_to_file();
    last_print_clock = std::clock();
    optimizer.set_step_size(65536 * std::numeric_limits<T>::epsilon());
    while (true) {
        if (!optimizer.step()) {
            optimizer.print(print_prec);
            std::cout << "Located candidate local minimum." << std::endl;
            optimizer.write_to_file();
            if (mode == SearchMode::EXPLORE) { goto reset_d; }
            std::exit(EXIT_SUCCESS);
        }
        if (optimizer.get_iteration_count() % 1000 == 0) {
            optimizer.write_to_file();
        }
        if (mode == SearchMode::EXPLORE &&
            optimizer.get_iteration_count() >= 100000) {
            std::cout << "NOTICE: Exceeded maximum number "
                         "of BFGS iterations. Restarting from "
                         "new random point." << std::endl;
            goto reset_d;
        }
        const std::clock_t current_clock = std::clock();
        if (current_clock - last_print_clock >= clocks_between_prints) {
            optimizer.print(print_prec);
            last_print_clock = current_clock;
        }
    }
}

int main(int argc, char **argv) {
    const auto clocks_between_prints = static_cast<std::clock_t>(
            get_print_period(argc, argv) * CLOCKS_PER_SEC);
    const int prec = get_precision(argc, argv);
    const int print_prec = get_print_precision(argc, argv);
    const SearchMode mode = (argc >= 5)
                            ? SearchMode::REFINE
                            : SearchMode::EXPLORE;
    if (prec == float_limits::digits) {
        run_main_loop<float>(argv, mode, print_prec, clocks_between_prints);
    } else if (prec == double_limits::digits) {
        run_main_loop<double>(argv, mode, print_prec, clocks_between_prints);
    } else {
        run_main_loop<long double>(
                argv, mode, print_prec, clocks_between_prints);
    }
}