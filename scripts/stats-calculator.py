#!/usr/bin/env python

import os
import json
import argparse


def calculate_cache_hit_ratio(cache_misses, cache_accesses):
    return (int(cache_accesses) - int(cache_misses)) / int(cache_accesses)


def merge_log_files(logs_folder_path):
    merged_log_files = []
    for root_name, dir_names, file_names in os.walk(logs_folder_path):
        for file_name in file_names:
            file_path = os.path.join(root_name, file_name)
            if file_path.endswith('.json'):
                with open(file_path) as file:
                    file_json = json.load(file)
                    merged_log_files.append(file_json['threads']['0']['regions'])
    return merged_log_files


def calculate_cache_hit_ratio_per_region(logs_folder_path):
    merged_log_files = merge_log_files(logs_folder_path)

    cache_hit_ratio_per_region = {}
    for file in merged_log_files[1:]:
        for id, region in file.items():
            if f"{region['name']}" not in cache_hit_ratio_per_region:
                cache_hit_ratio_per_region[f"{region['name']}"] = []
            cache_hit_ratio_per_region[f"{region['name']}"].append(calculate_cache_hit_ratio(region['PAPI_L1_DCM'],
                                                                             region['PAPI_L1_DCA']))

    return cache_hit_ratio_per_region


def calculate_average_cache_hit_ratio_per_region(logs_folder_path, output_file_path):
    cache_hit_ratio_per_region = calculate_cache_hit_ratio_per_region(logs_folder_path)

    average_cache_hit_ratio_per_region = {}
    for name, cache_hit_ratio_per_region in cache_hit_ratio_per_region.items():
        average_cache_hit_ratio_per_region[f"{name}"] = sum(cache_hit_ratio_per_region)/len(cache_hit_ratio_per_region)

    with open(output_file_path, 'w') as file:
        json.dump(average_cache_hit_ratio_per_region, file)


def main():
    parser = argparse.ArgumentParser(description='Parse and aggregate generated PAPI logs.')
    parser.add_argument('-p', '--path', type=str, dest="logs_folder_path", required=True, help='Path to generated '
                                                                                               'PAPI logs')
    parser.add_argument('-o', '--output', type=str, dest="output_file_path", required=True, help='The file path to '
                                                                                                 'save the '
                                                                                                 'aggregated logs to')
    args = parser.parse_args()
    calculate_average_cache_hit_ratio_per_region(args.logs_folder_path, args.output_file_path)


if __name__ == "__main__":
    main()
