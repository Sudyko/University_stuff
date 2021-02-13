#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;

double __fastcall GetSum(vector<double>& nums) {
	double sum = 0;
	for (double& item : nums) {
		sum += item;
	}
	return sum;
}

double __fastcall GetMultiplication(vector<double>& nums) {
	double result = 1;
	for (double& item : nums) {
		result *= item;
	}
	return result;
}

void __fastcall PrintVector(vector<double>& nums) {
	for (auto& item : nums) {
		printf("%lg ", item);
	}
	printf("\n");
}

vector<double> __fastcall GetRelativeValues(vector<double>& nums, double& division) {
	vector<double> result;
	for (double& item : nums)
		result.push_back(GetRelative_by_Absolute(item, division));
	return result;
}

double __fastcall GetAbsolute(double& a, double& b) { return abs(a - b); }
double __fastcall GetRelative(double& a, double& b) { return GetAbsolute(a, b) / a; }
double __fastcall GetRelative_by_Absolute(double& a, double& b) { return a / b; }
double __fastcall GetAverage(vector<double>& nums) { return GetSum(nums) / nums.size(); }

int main() {
	double a, b;
	printf("Enter exact value and then approximated value.\n");
	scanf_s("%lg%lg", &a, &b);
	printf("Exact value: %lg\n", a);
	printf("Approximate value: %lg\n", b);
	printf("Absolute error: %lg\n", GetAbsolute(a, b));
	printf("Relative error: %lg\n\n", GetRelative(a, b));
	
	printf("Enter division value and length | format: 1 200\n");
	scanf_s("%lg%lg", &a, &b);
	printf("Division value: %lg\nLength: %lg\n", a, b);
	printf("Relative error for division: %lg\n\n", GetRelative_by_Absolute(a, b));
	
	printf("Enter number of elements in array.\n");
	int n;
	scanf_s("%d", &n);
	vector<double> result;
	vector<double> real;
	printf("Enter result height and real height | format: 100 99\n");
	for (n; n > 0; --n) {
		scanf_s("%lg", &a);
		result.push_back(a);
		scanf_s("%lg", &b);
		real.push_back(b);
	}
	printf("Real height: ");
	PrintVector(real);
	printf("Result height: ");
	PrintVector(result);
	double real_sum = GetSum(real);
	double result_sum = GetSum(result);
	printf("Real sum: %lg\nResult sum: %lg\n", real_sum, result_sum);
	printf("Absolute error: %lg < %d\n\n", GetAbsolute(real_sum, result_sum), real.size());

	printf("Enter real weight.\n");
	scanf_s("%lg", &a);
	printf("Enter number of elements in weight's array and then weight values.\n");
	scanf_s("%d", &n);
	vector<double> weights;
	for (n; n > 0; --n) {
		scanf_s("%lg", &b);
		weights.push_back(b);
	}
	printf("Real weight: %lg\nWeight array: ", a);
	PrintVector(weights);
	double avg = GetAverage(weights);
	printf("Average: %lg\n", avg);
	printf("Absolute error: %lg\n", GetAbsolute(a, avg));
	printf("Relative error: %lg\n\n", GetRelative(a, avg));

	result.clear();
	real.clear();
	printf("Enter number of elements in array.\n");
	scanf_s("%d", &n);
	printf("Enter result weight, length and real weight, length | format: result real\n");
	for (n; n > 0; --n) {
		scanf_s("%lg%lg", &a, &b);
		result.push_back(a);
		real.push_back(b);
	}
	printf("Result values: ");
	PrintVector(result);
	printf("Real values: ");
	PrintVector(real);
	double result_mult = GetMultiplication(result);
	double real_mult = GetMultiplication(real);
	printf("Result multiplication: %lg\n", result_mult);
	printf("Real multiplication: %lg\n\n", real_mult);
	printf("Enter division value.\n");

	double division;
	scanf_s("%lg", &division);
	vector<double> relative_values = GetRelativeValues(real, division);
	printf("Relative values: ");
	PrintVector(relative_values);
	printf("Relative error: %lg < %lg\n", GetRelative(real_mult, result_mult), GetSum(relative_values));
	return 0;
}