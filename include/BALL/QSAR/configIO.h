#ifndef CONFIG_IO_H
#define CONFIG_IO_H

#include <istream>
#include <BALL/DATATYPE/string.h>
#include <BALL/QSAR/sortedList.h>
#include <istream> 
 
namespace BALL
{
	namespace QSAR
	{
		struct InputConfiguration
		{
			InputConfiguration();
			
			String sd_file;
			SortedList<int> activities;
			bool read_sd_descriptors;
			bool center_data;
			bool center_y;
			String output;
			double validation_fraction;
			bool separate_activity_file;
			bool within_section;
			vector<String> csv_file;
			vector<int> csv_no_response;
			vector<bool> csv_desc_labels;
			vector<bool> csv_compound_labels;
			vector<String> csv_separator;
			bool nonnumeric_class_names;
			bool done;
		};
		
		struct InputPartitioningConfiguration
		{
			InputPartitioningConfiguration(); 
			
			String input_file;
			double validation_fraction;
			int no_folds;
			int ID;
			bool done;
		};
		
		struct ModelConfiguration
		{
			ModelConfiguration();
			
			bool done;
			String data_file;
			String output;
			String descriptor_source_model;
			vector<double> model_parameters;
			int model_no; 
			int kernel_type;
			double kernel_par1;
			double kernel_par2;
			int k_fold;
			bool optimize_model_parameters;
			double grid_search_stepwidth;
			int grid_search_steps;
			int grid_search_recursions;
			bool within_section;
			bool no_training;
		};
		
		struct FeatureSelectionConfiguration
		{
			FeatureSelectionConfiguration();
			
			String model;
			String data_file;
			int feat_type;
			String output;
			int k_fold;
			bool within_section;
			String statistic_name;
			String selection_name;
			int statistic;
			bool remove_correlated;
			double cor_threshold;
			bool opt_model_after_fs;
			bool opt_kernel_after_fs;
			double quality_increase_cutoff;
			bool opt;
			bool done;
			int grid_search_steps;
			int grid_search_recursions;
			double grid_search_stepwidth;
			int opt_k_fold;
		};
		
		struct ValidationConfiguration
		{
			ValidationConfiguration();
			
			String model;
			String data;
			String validation_data;
			int val_type;
			String output;
			int k_folds;
			int bootstrap_samples;
			int no_of_permutation_tests;
			int statistic;
			String statistic_name;
			vector<String> external_predictions;
			bool for_visualization_only;
			bool done;
		};
		
		struct PredictionConfiguration
		{
			PredictionConfiguration();
			
			String model;
			String data;
			String output;
			int statistic;
			String statistic_name;
			bool print_expected;
			bool done;
		};
		
		
		class ConfigIO
		{
			public:
				
				static void putbackLine(std::istream* input,String& line);
				
				static ModelConfiguration readModelConfiguration(std::istream* input);
		
				static FeatureSelectionConfiguration readFeatureSelectionConfiguration(std::istream* input);
		
				static InputConfiguration readInputConfiguration(std::istream* input);
		
				static InputPartitioningConfiguration readInputPartitioningConfiguration(std::istream* input);
				
				static ValidationConfiguration readValidationConfiguration(std::istream* input);
				
				static PredictionConfiguration readPredictionConfiguration(std::istream* input);		
		};
	}
}


#endif // CONFIG_IO_H