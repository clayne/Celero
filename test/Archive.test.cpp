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

#include <celero/Archive.h>
#include <gtest/gtest.h>

TEST(Archive, Instance)
{
	EXPECT_NO_THROW(celero::Archive::Instance());
}

TEST(Archive, setFileName)
{
	auto& x = celero::Archive::Instance();

	EXPECT_NO_THROW(x.setFileName(std::string{}));
	EXPECT_NO_THROW(x.setFileName(std::string{"Foo"}));
	EXPECT_NO_THROW(x.setFileName(std::string{"Foo/Bar"}));
	EXPECT_NO_THROW(x.setFileName(std::string{"Foo_Bar"}));
	EXPECT_NO_THROW(x.setFileName(std::string{"Foo_Bar.xml"}));
	EXPECT_NO_THROW(x.setFileName(std::string{"Foo Bar.xml"}));
}

TEST(Archive, add)
{
	auto& x = celero::Archive::Instance();

	celero::Experiment* e{nullptr};
	auto result = std::make_shared<celero::ExperimentResult>(e);

	EXPECT_TRUE(result != nullptr);
	EXPECT_NO_THROW(x.add(result));
	EXPECT_NO_THROW(x.add(nullptr));
}

TEST(Archive, save)
{
	auto& x = celero::Archive::Instance();

	EXPECT_NO_THROW(x.save());
	EXPECT_NO_THROW(x.setFileName(std::string{"Foo"}));
	EXPECT_NO_THROW(x.save());
}

TEST(Archive, setFileNameInvalidCharacters)
{
	auto& archive = celero::Archive::Instance();

	// Test invalid characters in file name
	EXPECT_NO_THROW(archive.setFileName(std::string{"Invalid\\Name"}));
	EXPECT_NO_THROW(archive.setFileName(std::string{"Invalid/Name"}));
	EXPECT_NO_THROW(archive.setFileName(std::string{"*Invalid:Name"}));
}

TEST(Archive, addInvalidExperimentResult)
{
	auto& archive = celero::Archive::Instance();

	// Test adding an invalid experiment result (null experiment pointer)
	celero::Experiment* invalidExperiment = nullptr;
	auto invalidResult = std::make_shared<celero::ExperimentResult>(invalidExperiment);

	EXPECT_TRUE(invalidResult != nullptr);
	EXPECT_NO_THROW(archive.add(invalidResult));

	// Test adding a completely null experiment result
	std::shared_ptr<celero::ExperimentResult> nullResult = nullptr;
	EXPECT_NO_THROW(archive.add(nullResult));
}

TEST(Archive, saveToInvalidPath)
{
	auto& archive = celero::Archive::Instance();

	// Set an invalid file path and attempt to save
	archive.setFileName(std::string{"/invalid/path/Foo.xml"});
	EXPECT_NO_THROW(archive.save());

	// Set an extremely long file name
	const int ArbitrarilyLargeFileName = 5000;
	std::string longFileName(ArbitrarilyLargeFileName, 'x');
	archive.setFileName(longFileName);
	EXPECT_NO_THROW(archive.save());
}
