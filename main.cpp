#include "TorchManipulation.h"
int main()
{

		ml::MLModelsContainer::FC = torch::jit::load("Feasibility_Predictor.pt");  		// load the feasibility predictor
		ml::MLModelsContainer::FC.eval();												
		torch::Tensor features = ml::ExtractFeatures(items);							// extract features from items
		std::vector<torch::jit::IValue> inputs;											// declare the inputs
		inputs.push_back(features);														// assign the inputs of the model by the extracted features
		at::Tensor y = ml::MLModelsContainer::FC.forward(inputs).toTensor();			// get the output
		std::cout<<y.item<double>();													// get the value of y as a double type

}