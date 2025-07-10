#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct MapRange {
    ll dest_start, source_start, range_length;
};

ll apply_map(ll value, const vector<MapRange>& map) {
    for (const auto& range : map) {
        if (value >= range.source_start && value < range.source_start + range.range_length) {
            return range.dest_start + (value - range.source_start);
        }
    }
    return value;
}

struct Interval {
    ll start, end;
    
    Interval(ll s, ll e) : start(s), end(e) {}
    bool empty() const { return start >= end; }
};

vector<Interval> apply_map_to_intervals(vector<Interval> intervals, const vector<MapRange>& map) {
    vector<Interval> result;
    
    for (Interval interval : intervals) {
        queue<Interval> to_process;
        to_process.push(interval);
        
        for (const MapRange& range : map) {
            int queue_size = to_process.size();
            
            for (int i = 0; i < queue_size; i++) {
                Interval current = to_process.front();
                to_process.pop();
                
                ll map_start = range.source_start;
                ll map_end = range.source_start + range.range_length;
                
                ll intersect_start = max(current.start, map_start);
                ll intersect_end = min(current.end, map_end);
                
                if (intersect_start < intersect_end) {
                    ll offset = range.dest_start - range.source_start;
                    result.push_back(Interval(intersect_start + offset, intersect_end + offset));
                    
                    if (current.start < intersect_start) {
                        to_process.push(Interval(current.start, intersect_start));
                    }
                    if (intersect_end < current.end) {
                        to_process.push(Interval(intersect_end, current.end));
                    }
                } else {
                    to_process.push(current);
                }
            }
        }
        
        while (!to_process.empty()) {
            result.push_back(to_process.front());
            to_process.pop();
        }
    }
    
    return result;
}

int main() {
    string seed_str;
    getline(cin, seed_str);
    stringstream ss(seed_str);
    ss.ignore(INT_MAX, ':');
    ll seed;
    vector<ll> seeds;
    while (ss >> seed) {
        seeds.push_back(seed);
    }
    
    string line;
    getline(cin, line);
    
    vector<vector<MapRange>> maps;
    
    while (getline(cin, line)) {
        if (line.empty()) continue;
        
        if (line.find("map:") != string::npos) {
            vector<MapRange> current_map;
            
            while (getline(cin, line) && !line.empty()) {
                stringstream map_ss(line);
                ll dest, source, length;
                map_ss >> dest >> source >> length;
                current_map.push_back({dest, source, length});
            }
            
            maps.push_back(current_map);
        }
    }
    
    ll min_location_part1 = LLONG_MAX;
    
    for (ll current_seed : seeds) {
        ll current_value = current_seed;
        
        for (const auto& map : maps) {
            current_value = apply_map(current_value, map);
        }
        
        min_location_part1 = min(min_location_part1, current_value);
    }
    
    vector<Interval> current_intervals;
    
    for (int i = 0; i < seeds.size(); i += 2) {
        ll range_start = seeds[i];
        ll range_length = seeds[i + 1];
        current_intervals.push_back(Interval(range_start, range_start + range_length));
    }
    
    for (const auto& map : maps) {
        current_intervals = apply_map_to_intervals(current_intervals, map);
    }
    
    ll min_location_part2 = LLONG_MAX;
    for (const Interval& interval : current_intervals) {
        if (!interval.empty()) {
            min_location_part2 = min(min_location_part2, interval.start);
        }
    }
    
    cout << "Part 1: " << min_location_part1 << endl;
    cout << "Part 2: " << min_location_part2 << endl;
    
    return 0;
}
