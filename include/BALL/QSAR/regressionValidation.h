/* regressionValidation.h
 * 
 * Copyright (C) 2009 Marcel Schumann
 * 
 * This file is part of QuEasy -- A Toolbox for Automated QSAR Model
 * Construction and Validation.
 * QuEasy is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 * 
 * QuEasy is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//
//

#ifndef REGVALIDATION
#define REGVALIDATION

#ifndef QSARDATA
#include <BALL/QSAR/QSARData.h>
#endif

#ifndef VALIDATION
#include <BALL/QSAR/validation.h>
#endif

#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>
#include <iterator>


#include <BALL/MATHS/LINALG/matrix.h>
#include <BALL/MATHS/LINALG/vector.h>



namespace BALL
{	
	namespace QSAR
	{
		class RegressionModel;
		/** class for validation of QSAR regression models */
		class BALL_EXPORT RegressionValidation : public Validation
		{	
			public:
				/** @name Constructors and Destructors
				 */
				//@{
				/** constructor
				@param m pointer to the regression model, which the object of this class should test */
				RegressionValidation(RegressionModel* m);

				~RegressionValidation();
				//@}
				
				
				/** @name Accessors
				 */
				//@{
				/** starts k-fold cross validation \n
				@param k no of cross validation folds
				@param restore if restore==1, Model.descriptor_matrix and RegressionModel.training_result is restored after cross validation */
				void crossValidation(int k, bool restore=1);
				
				/** starts k-fold cross validation \n
				@param k no of cross validation folds
				@param restore if restore==1, Model.descriptor_matrix and RegressionModel.training_result is restored after cross validation 
				@param results pointer to vector that should take all matrices RegressionModel.training_result produced during this cross validation run */
				void crossValidation(int k, vector<BALL::Matrix<double> >* results, bool restore=1);
				
				
				/** starts bootstrapping with k samples \n
				@param k no of bootstrap samples
				@param restore if restore==1, Model.descriptor_matrix and RegressionModel.training_result is restored after bootstrapping */
				void bootstrap(int k, bool restore=1);
				
				/** starts bootstrapping with k samples \n
				@param k no of bootstrap samples
				@param restore if restore==1, Model.descriptor_matrix and RegressionModel.training_result is restored after bootstrapping
				@param results pointer to vector that should take all matrices RegressionModel.training_result produced during this bootstrapping */
				void bootstrap(int k, vector<BALL::Matrix<double> >* results, bool restore=1);
				
				void bootstrap1(int k, vector<BALL::Matrix<double> >* results, bool restore=1);
				
				/** Y randomization test \n
				Randomizes all columns of model.Y, trains the model, runs crossValidation and testInputData and saves the resulting R2 and Q2 value to a matrix with 2 columns; the R2 values makeing up the first colum, the Q2 value the second.
				@param runs this is repeated as often as specified by 'runs' */
				const BALL::Matrix<double>& yRandomizationTest(int runs, int k);
				
				/** get the Q^2 value.\n
				If no cross-validation has been done yet, -1 is returned */
				double getQ2();
				
				/** get the R^2 value.\n
				If testInputData() has not been run yet, -1 is returned */
				double getR2();		
				
				/** get the F-value as calculated by testInputData().\n
				If testInputData() has not been run yet, -1 is returned */
				double getFregr();
						
				/** get the F-value as calculated by cross validation.\n
				If crossValidation() has not been run yet, -1 is returned */
				double getFcv();
				
				double getCVRes();
				
				double getFitRes();
				
				/** returns the maximal error of the prediction */
				double getMaxError();
				
				void setCVRes(double d);
		
				/** set the Q^2 value */
				void setQ2(double d);
				
				void testInputData(bool transform=0);
				
				/** select the desired statistic to be used for validating the models
				@param s if (s==1) R^2 and Q^2 are used \n
					if(s==2) F_regr and F_cv are used. */
				void selectStat(int s);
				
				/** calculates standart deviations for all predicted coefficients and saves them to coefficient_stddev_ \n
				@param b if b==1, bootstrapping is used; else: cross-validation
				@param k number of bootstrap samples resp. cross-validation steps */
				void calculateCoefficientStdErrors(int k, bool b=1);
			
				/** returns a const pointer to the matrix containing the standart deviations of all predicted coefficients */
				const BALL::Matrix<double>* getCoefficientStdErrors();
				
				void setCoefficientStdErrors(const BALL::Matrix<double>* stddev);
				
				void saveToFile(string filename) const;
				
				void saveToFile(string filename, const double& r2, const double& q2, const Matrix<double>& coefficient_stddev, const Matrix<double>& yRand_results) const;
				
				void readFromFile(string filename);
				//@}
				
	
			private:
				
				struct BackupData
				{
					Matrix<double> descriptor_matrix;
					Matrix<double> training_result;
					Matrix<double> Y;
					Matrix<double> K;
					Matrix<double> latent_variables;
					Matrix<double> loadings;
					Matrix<double> weights;
				};
				
				
				/** @name Accessors
				 */
				//@{	
				/** Tests the current model with all substances in the (unchanged) test data set */
				void testAllSubstances(bool transform);
				
				void backupTrainingResults();
				
				void restoreTrainingResults();
				//@}
				
				
				/** @name Attributes
				 */
				//@{
				
				double ssR_;
				
				double ssE_;
				
				/** the sum of squares of the response */
				double ssY_;
				
				/** standart error */
				double std_err_;
	
				/** Q^2-value as calculated after cross-validation */
				double Q2_;
	
				/** F-value as calculated after cross-validation */
				double F_cv_;
				
				/** F-value as calculated after regression for input data  */
				double F_regr_;
	
				double R2_;
				
				double max_error_;
				
				/** the quality as calcated by the last call of testAllSubstances() according to the chose quality-statistic */
				double quality_;
				
				double (RegressionValidation::* predQualFetcher_)();
				
				double (RegressionValidation::* fitQualFetcher_)();
				
				void calculateQOF();
				
				/** contains the standart deviations of all predicted coefficients in one column for each modelled activity */
				BALL::Matrix<double> coefficient_stderr_;
				
				/** pointer to the regression model, which the object of this class should test */
				RegressionModel* regr_model_;
				
				BackupData backup_data_;
				
				void (RegressionValidation::* qualCalculation)();
				//@}				
				
		};
	}
}



#endif // REGVALIDATION