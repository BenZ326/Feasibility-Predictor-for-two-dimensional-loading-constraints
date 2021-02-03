#include "TorchManipulation.h"

torch::jit::script::Module ml::MLModelsContainer::FC;
torch::Tensor ml::TransItemsTensor(const std::list<const Rectangle*>& t_rectanlges)
{
	
	torch::Tensor  result;
	std::vector<torch::Tensor> tmpTensorsVec;
	for (const auto& it : t_rectanlges)
	{
		torch::Tensor  itemImagePacked = torch::ones({GlobalParam::parameters()->getMaxBinWidth(), 
			GlobalParam::parameters()->getMaxBinHeight()})* -1;
		for (int i = 0; i < ObjMgr::instance()->getWidth(); ++i)
		{
			for (int j = 0; j < ObjMgr::instance()->getHeight(); ++j)
			{
				if (i >= it->getWidth() || j >= it->getHeight())
					itemImagePacked[i][j] = 0;
				else
					itemImagePacked[i][j] = 1;
			}
		}
		tmpTensorsVec.push_back(itemImagePacked);
	}

	result = torch::zeros({int(tmpTensorsVec.size()), 
		GlobalParam::parameters()->getMaxBinWidth(), GlobalParam::parameters()->getMaxBinHeight()});
	for (size_t i = 0; i < tmpTensorsVec.size(); ++i)
	{
		result[i] = tmpTensorsVec[i];
	}
	result = result.unsqueeze(0);
	return result;
}


torch::Tensor ml::ExtractFeatures(const std::list<const Rectangle*>& t_rectanlges)
{
	// w/h
	torch::Tensor result = torch::zeros({1,numberFeatures });
	float binCapacity = float(ObjMgr::instance()->getHeight() * ObjMgr::instance()->getWidth());
	std::vector<float> w_h_ratio;
	for (const auto& it : t_rectanlges)
	{
		w_h_ratio.push_back((float(it->getWidth()) / float(it->getHeight()))/ maxWHRatio);
	}
	auto mean_w_h_ratio = myMathsLib::getMean(w_h_ratio) ;
	auto std_w_h_ratio = myMathsLib::getStd(w_h_ratio);
	auto min_w_h_ratio = *std::min_element(w_h_ratio.begin(), w_h_ratio.end());
	auto max_w_h_ratio = *std::max_element(w_h_ratio.begin(), w_h_ratio.end());
	result[0][0] = mean_w_h_ratio;
	result[0][1] = min_w_h_ratio;
	result[0][2] = max_w_h_ratio;
	result[0][3] = std_w_h_ratio;
	// w/W
	std::vector<float> w_W_ratio;
	for (const auto& it : t_rectanlges)
	{
		w_W_ratio.push_back(float(it->getWidth()) / float(ObjMgr::instance()->getWidth()));
	}
	auto mean_w_W_ratio = myMathsLib::getMean(w_W_ratio);
	auto std_w_W_ratio = myMathsLib::getStd(w_W_ratio);
	auto min_w_W_ratio = *std::min_element(w_W_ratio.begin(), w_W_ratio.end());
	auto max_w_W_ratio = *std::max_element(w_W_ratio.begin(), w_W_ratio.end());
	result[0][4] = mean_w_W_ratio;
	result[0][5] = min_w_W_ratio;
	result[0][6] = max_w_W_ratio;
	result[0][7] = std_w_W_ratio;
	// h/H
	std::vector<float> h_H_ratio;
	for (const auto& it : t_rectanlges)
	{
		h_H_ratio.push_back(float(it->getHeight()) / float(ObjMgr::instance()->getHeight()));
	}
	auto mean_h_H_ratio = myMathsLib::getMean(h_H_ratio);
	auto std_h_H_ratio = myMathsLib::getStd(h_H_ratio);
	auto min_h_H_ratio = *std::min_element(h_H_ratio.begin(), h_H_ratio.end());
	auto max_h_H_ratio = *std::max_element(h_H_ratio.begin(), h_H_ratio.end());
	result[0][8] = mean_h_H_ratio;
	result[0][9] = min_h_H_ratio;
	result[0][10] = max_h_H_ratio;
	result[0][11] = std_h_H_ratio;
	// area/bin capacity
	std::vector<float> area_Capacity_ratio;
	for (const auto& it : t_rectanlges)
	{
		area_Capacity_ratio.push_back(float(it->getArea()) / binCapacity);
	}
	auto mean_area_Capacity_ratio = myMathsLib::getMean(area_Capacity_ratio);
	auto std_area_Capacity_ratio = myMathsLib::getStd(area_Capacity_ratio);
	auto min_area_Capacity_ratio = *std::min_element(area_Capacity_ratio.begin(), area_Capacity_ratio.end());
	auto max_area_Capacity_ratio = *std::max_element(area_Capacity_ratio.begin(), area_Capacity_ratio.end());
	result[0][12] = mean_area_Capacity_ratio;
	result[0][13] = min_area_Capacity_ratio;
	result[0][14] = max_area_Capacity_ratio;
	result[0][15] = std_area_Capacity_ratio;
	//  total area / bin capacity 
	float totalArea = 0.0;
	for (const auto& it : t_rectanlges)
	{
		totalArea += it->getArea();
	}
	float total_area_Capacity = totalArea / (binCapacity);
	result[0][16] = total_area_Capacity;
	return result;
}