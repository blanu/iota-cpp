rm -rf profiling.trace
xcrun xctrace record --template 'Time Profiler' --launch cmake-build-release/bin/iota-tests "AoC_2025_2_1 full" --output profiling.trace
xcrun xctrace export --input profiling.trace --xpath '/trace-toc/run[@number="1"]/data/table[@schema="time-profile"]' --output time_profile.xml
xcrun xctrace export --input profiling.trace --xpath '/trace-toc/run[@number="1"]/data/table[@schema="time-sample"]' --output time_samples.xml
