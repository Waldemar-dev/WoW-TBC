#include <fstream>
#include <iostream>
#include <cstdlib>
#include "TMatrix.h"
using namespace std;

std::function<double(const double *)> fit_scaling_output(std::function<double(const double *)> fit_tps)
{
    std::function<double(const double *)> out = [fit_tps](const double *args) -> double
    { return fit_tps(args); };
    return out;
}

std::function<double(const double *)> fit_scaling(TMatrixD statMatrix, TVectorD dataVec)
{
    std::function<double(const double *)> out = [statMatrix, dataVec](const double *args)
        -> double
    {
        double result;
        double agiCoef = 1/args[0];
        double dodgeRatingCoef = 1/args[1];
        double defenseRatingCoef = 1/args[2];
        double offset = args[3];
        for (uint i = 0; i < dataVec.GetNrows(); i++)
        {
            double temp = statMatrix[i][0] * agiCoef + statMatrix[i][1] * dodgeRatingCoef + max(0.04 * (statMatrix[i][2] * defenseRatingCoef - 15),0.0) + offset;
            result += pow(temp+2.62 - dataVec[i], 2);
        }
        return result / (double)dataVec.GetNrows();
    };
    return out;
}

void fit_dodge_stats()
{
    vector<vector<double>> read_data;
    double x1, x2, x3, y;
    ifstream in_data;
    in_data.open("fit_data.dat");
    while (!in_data.eof())
    {
        in_data >> x1 >> x2 >> x3 >> y;
        vector<double> temp = {x1, x2, x3, y};
        read_data.push_back(temp);
    }
    read_data.shrink_to_fit();
    TMatrixD stat_matrix(read_data.size(), read_data[0].size() - 1);
    TVectorD data(read_data.size());
    for (uint i = 0; i < read_data.size(); i++)
    {
        for (uint j = 0; j < read_data[i].size() - 1; j++)
        {
            stat_matrix[i][j] = read_data[i][j];
        }
        data[i] = read_data[i].back();
    }
    std::vector<std::string> temp_names = {"agiCoef", "dodgeRatingCoef", "defenseRatingCoef", "offset"};
    ROOT::Math::Minimizer *minimizer = ROOT::Math::Factory::CreateMinimizer("Minuit2", "Migrad");
    std::function<double(const double *)> scaling_fit = fit_scaling(stat_matrix, data);
    std::function<double(const double *)> scaling_fit_output = fit_scaling_output(scaling_fit);
    minimizer->SetMaxFunctionCalls(0);
    ROOT::Math::Functor f = ROOT::Math::Functor(scaling_fit, temp_names.size());
    minimizer->SetFunction(f);
    srand(time(NULL));
    double metric = DBL_MAX;
    double tolerance = pow(10, -4);
    vector<double> my_args;
    while (metric > tolerance)
    {
        for (uint i = 0; i < temp_names.size(); i++)
        {
            double temp_initial_value = rand() / (double)RAND_MAX;
            minimizer->SetVariable(i, temp_names[i].c_str(), temp_initial_value, pow(10, -5));
        }
        minimizer->Minimize();
        vector<double> args_vec;
        args_vec.reserve(temp_names.size());
        for (uint i = 0; i < temp_names.size(); i++)
        {
            args_vec.push_back(minimizer->X()[i]);
        }
        double *args = args_vec.data();
        double temp_metric = scaling_fit_output(args);
        if (temp_metric < metric)
        {
            my_args = args_vec;
            metric = temp_metric;
            cout << metric << endl;
            for (uint i = 0; i < my_args.size(); i++)
            {
                cout << my_args[i] << "\t";
            }
            cout<<endl;
        }
    }
    cout<<"best result:"<<endl;
    cout << metric << endl;
    for (uint i = 0; i < my_args.size(); i++)
    {
        cout << my_args[i] << "\t";
    }
}