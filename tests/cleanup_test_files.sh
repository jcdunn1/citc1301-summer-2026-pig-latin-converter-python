#!/bin/bash

# Stop on error
set -e

echo "Cleaning up test files..."

# Remove test folders and their contents
rm -rf tests/test01
rm -rf tests/test02
rm -rf tests/test03
rm -rf tests/test04

echo "All test input and output files removed."