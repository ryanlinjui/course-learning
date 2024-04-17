// NOJ Problem #484 - Speaker Diarization

#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <stdint.h>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
	
	uint32_t n = 0, l = 0;
	vector<pair<uint32_t,uint32_t>> data;
	cin >> n >> l;
	for (int i = 0; i < n; i++)
	{
		pair<uint32_t,uint32_t> a;
		cin >> a.first >> a.second;
		if(a.first != a.second) data.push_back(a);
	}
	sort (data.begin(),data.end());

	uint32_t min_segment = 0, no_speak_time = 0;
	uint32_t end = 0, tmp_end = 0;

	if(data.size() > 0)
	{
		min_segment = 1;
		no_speak_time = data[0].first;
		end = data[0].second;
		tmp_end = data[0].second;
	}

	for (int i = 1; i < data.size(); i++)
	{	
		if(data[i].first <= end && i!=data.size()-1)
		{
			tmp_end	= max(tmp_end, data[i].second);
		}
		else
		{	
			if(data[i].first > tmp_end) 
			{
				no_speak_time += (data[i].first - end);
				if(i>1)
				{
					if(data[i].first - end > 0 && data[i-2].first != data[i-1].first) min_segment++;
				}
			}
			if(i!=data.size()-1) min_segment++;
			tmp_end	= max(tmp_end, data[i].second);
			if(i==data.size()-1 && tmp_end > end) min_segment++;
			end = tmp_end;
		}
	}	
	no_speak_time += (l - tmp_end);

	cout << min_segment << " " << no_speak_time << endl;
	return 0;
}