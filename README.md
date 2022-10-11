# Requirements:

- Visual Studio 20xx
- Windows PC

# How to use:

1. Git clone entire repo to folder of choice
2. Open .soln file in `TelepathyLabsTest` folder
3. There should be 4 projects, `TLT_Qn_1`, `TLT_Qn_2`, `UnitTests_Qn_1`, `UnitTests_Qn_2`
4. `TLT_Qn_1` and `TLT_Qn_2` contain answer code, `UnitTests_Qn_X` contain the google unit tests for the corresponding answers
5. Rightclick project of choice in Solution Explorer (only `UnitTests` can be run, other projects are set to be compiled as static libraries, so no .exe)
6. In context menu, choose Debug->Start New Instance to run the unit test of choice
7. Train of thought for unit tests contained within comments in unit test code
