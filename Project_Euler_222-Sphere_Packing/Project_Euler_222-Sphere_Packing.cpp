
// Project Euler #222: Sphere packing  |  HackerRank Challenges


#include <iostream>
#include <vector>
#include <algorithm>	// sort()
#include <cmath>
#include <iomanip>	    // std::setprecision()


// Methods

std::vector<size_t> insertRadii(size_t n){

	size_t r;
    std::vector<size_t> radii_input_vector;

    // std::ifstream fileAlias("fileName.txt");		// #include <fstream>
	// fileAlias>>r;								// (You can use radii_test.txt,
                                                    //  which includes 20000 radii)
    // Fill the radii_input_vector
    while(n--){
        std::cin>>r;
        radii_input_vector.push_back(r*1000);		// mm to ìm
    }
    return radii_input_vector;
}

double getMinPipeLength(size_t R, std::vector<size_t> radii_input_vector){

	/* Sort the radii_input_vector vector, descenting. You can sort acenging,
     * without passing a 3rd argument [without std::greater<double>()].
     */
    sort(radii_input_vector.begin(), radii_input_vector.end(), std::greater<size_t>());

    /* Print-test of the radii_input_vector vector, descending
     std::cout<<"Sphere radii descending: ";
     for(size_t i=0; i<radii_input_vector.size(); ++i)
     std::cout<<radii_input_vector[i]<<" ";
     std::cout<<std::endl;*/

    // Devide the vector int two vectors, alternately
    std::vector<size_t> radii_1, radii_2;

    for(size_t i=0; i<radii_input_vector.size(); ++i){

        if(i%2==0)
        radii_1.push_back(radii_input_vector[i]);
        else if(i%2==1)
        radii_2.push_back(radii_input_vector[i]);
    }

	 	/* Printing test-block
		std::cout<<std::endl;
        std::cout<<"radii_1: ";
        for(size_t i=0; i<radii_1.size(); ++i)
        std::cout<<radii_1[i]<<" ";

        std::cout<<std::endl;

        std::cout<<"radii_2: ";
        for(size_t i=0; i<radii_2.size(); ++i)
        std::cout<<radii_2[i]<<" ";

        std::cout<<std::endl;*/


    // Building the final vector of the radii with the positioning sequence
    std::vector<size_t> radii_final = radii_1;

    for(size_t i=radii_2.size()-1; i!=-1; --i)
    radii_final.push_back(radii_2[i]);

    /* Print-test of the radii_final vector, index ascenting
     std::cout<<std::endl<<"Final radius order is: ";
     for(size_t i=0 ; i<radii_final.size() ; ++i)
     std::cout<<radii_final[i]<<" ";

     std::cout<<std::endl;*/


    // Filaly, calculate the length in query (l)

    // Initialize l with first + last radii
    double l=radii_final.front()+radii_final.back();
    // std::cout<<std::endl<<"length is initialized with r_0 + r_(n-1): "<<std::fixed<<l<<std::endl<<std::endl;

	// Add every y at length
    double c=0.0, y, t;
    for(size_t i=1; i<radii_final.size(); ++i){

    	// Kahan summation method
    	y=2*sqrt(R*(radii_final[i-1]+radii_final[i]-R))-c;
    	//std::cout<<"New square root"<<std::endl;
    	//std::cout<<std::fixed<<std::setprecision(15)<<"y is: "<<y<<std::endl;
    	t=l+y;
    	//std::cout<<"t is: "<<t<<std::endl;
    	c=(t-l);
    	c-=y;
    	//std::cout<<"c is: "<<c<<std::endl;
    	l=t;
    	//std::cout<<"l is: "<<l<<std::endl<<std::endl;

    	// Without Kahan algorithm = naive summation
    	// l=l+2*sqrt((double)R*((double)radii_final[i-1]+(double)radii_final[i]-(double)R));

		// std::cout<<"Square root No "<<i<<" is: ";
		// stc::cout<<sqrt((double)R*((double)radii_final[i-1]+(double)radii_final[i]-(double)R))<<std::endl;
    }

	return l;
}

int main(){

	// R = tube radius
    // n = number of spheres
    // r = sphere radius input
    size_t R, n;
    std::cin>>R>>n;
    R*=1000;	// mm to ìm

    std::cout<<std::fixed<<std::setprecision(0)<<getMinPipeLength(R, insertRadii(n));

}


