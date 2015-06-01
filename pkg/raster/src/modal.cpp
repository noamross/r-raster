#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export(name = ".getMode")]]
double getMode(NumericVector values, int ties) {

	int n = values.length();
    IntegerVector counts(n);

	if (ties < 3) {
		std::sort(values.begin(), values.end());
	}
	
    for (int i = 0; i < n; ++i) {
        counts[i] = 0;
        int j = 0;
        while ((j < i) && (values[i] != values[j])) {
            if (values[i] != values[j]) {
                ++j;
            }
        }
        ++(counts[j]);
    }
    int maxCount = 0;

	// first (lowest due to sorting)
	if (ties == 0) {
		for (int i = 1; i < n; ++i) {
			if (counts[i] > counts[maxCount]) {
				maxCount = i;
			}
		}
	// last	
	} else if (ties == 1) {
		for (int i = 1; i < n; ++i) {
			if (counts[i] >= counts[maxCount]) {
				maxCount = i;
			}
		}

	// dont care (first, but not sorted)
	} else if (ties == 2) {
		for (int i = 1; i < n; ++i) {
			if (counts[i] > counts[maxCount]) {
				maxCount = i;
			}
		}

	// random
	} else if (ties == 3) {
		for (int i = 1; i < n; ++i) {
			if (counts[i] > counts[maxCount]) {
				maxCount = i;
			} else if (counts[i] == counts[maxCount]) {
				if (R::runif(0,1) > 0.5) {
					maxCount = i;
				}			
			}
		}
	}
		
	
    return values[maxCount];
}


