///
/// \author	John Farrier
///
/// \copyright Copyright 2015, 2016, 2017 John Farrier
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
/// http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///

#include <celero/Benchmark.h>
#include <celero/Experiment.h>
#include <gtest/gtest.h>

TEST(Benchmark, ctor)
{
	EXPECT_NO_THROW(celero::Benchmark());
}

TEST(Benchmark, ctor_string)
{
	EXPECT_NO_THROW(celero::Benchmark(std::string{}));
	EXPECT_NO_THROW(celero::Benchmark(std::string{"Foo"}));
	EXPECT_NO_THROW(celero::Benchmark(std::string{"Foo.Bar"}));
	EXPECT_NO_THROW(celero::Benchmark(std::string{"Foo Bar"}));
}

TEST(Benchmark, ctor_copy)
{
	const auto name = std::string{"Foo"};
	celero::Benchmark original{name};
	celero::Benchmark copy(original);

	EXPECT_EQ(original.getName(), copy.getName());
}

TEST(Benchmark, getNameEmpty)
{
	const auto name = std::string{};
	celero::Benchmark x{};
	EXPECT_EQ(name, x.getName());
}

TEST(Benchmark, getName)
{
	const auto name = std::string{"Foo"};
	celero::Benchmark x(name);
	EXPECT_EQ(name, x.getName());
}

TEST(Benchmark, setBaseline)
{
	celero::Benchmark x{};
	auto baseline = std::make_shared<celero::Experiment>(std::shared_ptr<celero::Benchmark>(nullptr));

	EXPECT_NO_THROW(x.setBaseline(baseline));
	EXPECT_EQ(baseline, x.getBaseline());

	EXPECT_NO_THROW(x.setBaseline(nullptr));
	EXPECT_EQ(nullptr, x.getBaseline());
}

TEST(Benchmark, addExperiment)
{
	celero::Benchmark x{};
	auto experiment = std::make_shared<celero::Experiment>(std::shared_ptr<celero::Benchmark>(nullptr));
	EXPECT_NO_THROW(x.addExperiment(experiment));
}

TEST(Benchmark, getExperiment)
{
	celero::Benchmark x{};
	std::shared_ptr<celero::Experiment> experiment;

	EXPECT_NO_THROW(experiment = x.getExperiment(size_t{0}));
	EXPECT_EQ(nullptr, experiment);

	EXPECT_NO_THROW(experiment = x.getExperiment(size_t{999}));
	EXPECT_EQ(nullptr, experiment);

	experiment = std::make_shared<celero::Experiment>(std::shared_ptr<celero::Benchmark>(nullptr));
	EXPECT_NO_THROW(x.addExperiment(experiment));
	EXPECT_EQ(experiment, x.getExperiment(size_t{0}));
	EXPECT_EQ(nullptr, x.getExperiment(size_t{999}));
}

TEST(Benchmark, ctor_invalid_string)
{
	// Test with an invalid or very large string to check constructor robustness
	std::string longString(10000, 'x');
	EXPECT_NO_THROW(celero::Benchmark(longString));
}

TEST(Benchmark, addMultipleExperiments)
{
	celero::Benchmark benchmark{};

	auto experiment1 = std::make_shared<celero::Experiment>(std::shared_ptr<celero::Benchmark>(nullptr));
	auto experiment2 = std::make_shared<celero::Experiment>(std::shared_ptr<celero::Benchmark>(nullptr));

	EXPECT_NO_THROW(benchmark.addExperiment(experiment1));
	EXPECT_NO_THROW(benchmark.addExperiment(experiment2));

	// Ensure the experiments were added properly
	EXPECT_EQ(benchmark.getExperimentSize(), 2);
}

TEST(Benchmark, invalidBaseline)
{
	celero::Benchmark benchmark{};

	// Test setting a baseline with an invalid (null) experiment pointer
	std::shared_ptr<celero::Experiment> invalidBaseline = nullptr;
	EXPECT_NO_THROW(benchmark.setBaseline(invalidBaseline));
	EXPECT_EQ(benchmark.getBaseline(), nullptr);

	// Try setting a valid baseline after setting an invalid one
	auto validBaseline = std::make_shared<celero::Experiment>(std::shared_ptr<celero::Benchmark>(nullptr));
	EXPECT_NO_THROW(benchmark.setBaseline(validBaseline));
	EXPECT_EQ(benchmark.getBaseline(), validBaseline);
}

TEST(Benchmark, addInvalidExperiment)
{
	celero::Benchmark benchmark{};

	// Attempt to add a null experiment, which should not be allowed
	std::shared_ptr<celero::Experiment> nullExperiment = nullptr;
	EXPECT_THROW(benchmark.addExperiment(nullExperiment), std::runtime_error);
}
