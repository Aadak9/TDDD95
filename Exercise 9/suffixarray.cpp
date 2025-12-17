#include <iostream>
#include <vector>
#include <string>

std::string reconstruct(int n, const std::vector<std::pair<int,std::string>>& suffixes)
{
    std::vector<char> s(n, '?');

    for (auto& p : suffixes)
    {
        int pos = p.first - 1;
        std::string suf = p.second;
        size_t star = suf.find('*');

        if (star == std::string::npos)
        {
            for (size_t i = 0; i < suf.size(); ++i)
            {
                int idx = pos + i;
                if (idx >= n)
                {
                    return "IMPOSSIBLE";
                }
                if (s[idx] == '?' || s[idx] == suf[i])
                {
                    s[idx] = suf[i];
                }
                else
                {
                    return "IMPOSSIBLE";
                }
            }
        }
        else
        {
            std::string prefix = suf.substr(0, star);
            std::string suffix = suf.substr(star + 1);
            int prefixLen = prefix.size();
            int suffixLen = suffix.size();

            for (int i = 0; i < prefixLen; ++i)
            {
                int idx = pos + i;
                if (idx >= n)
                {
                    return "IMPOSSIBLE";
                }
                if (s[idx] == '?' || s[idx] == prefix[i])
                {
                    s[idx] = prefix[i];
                }
                else
                {
                    return "IMPOSSIBLE";
                }
            }

            for (int i = 0; i < suffixLen; ++i)
            {
                int idx = n - suffixLen + i;
                if (idx < pos + prefixLen || idx >= n)
                {
                    return "IMPOSSIBLE";
                }
                if (s[idx] == '?' || s[idx] == suffix[i])
                {
                    s[idx] = suffix[i];
                }
                else
                {
                    return "IMPOSSIBLE";
                }
            }
        }
    }

    for (int i = 0; i < n; ++i)
    {
        if (s[i] == '?')
        {
            s[i] = 'a';
        }
    }

    return std::string(s.begin(), s.end());
}

int main()
{
    int T;
    std::cin >> T;

    while (T--)
    {
        int n, m;
        std::cin >> n >> m;
        std::vector<std::pair<int,std::string>> suffixes(m);

        for (int i = 0; i < m; ++i)
        {
            std::cin >> suffixes[i].first >> suffixes[i].second;
        }

        std::string ans = reconstruct(n, suffixes);
        std::cout << ans << "\n";
    }

    return 0;
}



