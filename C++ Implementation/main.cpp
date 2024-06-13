#include "MonoCFTP.h"
#include "Model.h"
#include "Graph.h"
#include "IsingModel.h"


using std::string;
using std::vector;
using std::array;
using std::set;
using std::shared_ptr;



int main(){

    int seed = 69895;

    SquareLattice<short> latt(100, 2);
    shared_ptr<IsingModel> model = std::make_shared<IsingModel>(IsingModel(latt, .45));

    MonoCFTP cftp(model);
    shared_ptr<Model> result = cftp.sample(seed, 2, 1000);

    (std::dynamic_pointer_cast<IsingModel>(result))->save(std::to_string(seed) + "Ising_latt-100-2_45e-2.txt");

    return 0;
}