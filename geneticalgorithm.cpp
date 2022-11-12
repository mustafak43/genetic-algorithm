#include <iostream>
#include <vector>
using namespace std;

float const LR = 0.05; // Learning rate

float Activation(float g); // Activation function

class Perceptron
{
    vector<float> weights; // weights for inputs
    float bias;
    float bias_weight;

public:
    // ctor for initializing weights
    // with the value of 0.5
    Perceptron(int amount)
    {
        for (int i = 0; i < amount; i++)
            weights.push_back(0.5);
        bias = 1;
        bias_weight = 0.5;
    }

    float guess(vector<float> in)
    {
        // for error handling
        if (in.size() != weights.size())
            cout << "Input array's and weight array's sizes don't match !\n";
        else
        {
            float sum = 0;

            for (unsigned int i = 0; i < weights.size(); i++)
                sum += weights[i] * in[i];
            sum += bias * bias_weight;

            return sum;
        }
        return 0;
    }

    void adjust(vector<float> in, float err)
    {
        for (unsigned int i = 0; i < weights.size(); i++)
            weights[i] += err * in[i] * LR;
        bias_weight += err * bias * LR;
    }
};

int main()
{
    Perceptron perceptron(2);

    int iteration = 100; // amount of training

    // OR logical operator training dataset
    vector<vector<float>> inputs{ {1, 1}, {1, 0}, {0, 1}, {0, 0} };
    // desired outputs
    vector<float> outputs{ 1, 1, 1, 0 };

    float error = 0;

    // training
    for (int i = 0; i < iteration; i++)
    {
        for (unsigned int j = 0; j < inputs.size(); j++)
        {
            error = outputs[j] - Activation(perceptron.guess(inputs[j]));
            perceptron.adjust(inputs[j], error);
        }
    }

    // output should be : 1
    cout << Activation(perceptron.guess(inputs[0]));

    return 0;
}

float Activation(float g)
{
    if (g > 0)
        return 1;
    return 0;
}