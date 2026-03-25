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
            if (pos + (int)suf.size() != n)
            {
                return "IMPOSSIBLE";
            }

            for (size_t i = 0; i < suf.size(); ++i)
            {
                int idx = pos + i;

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

            int totalLen = n - pos;

            if (prefixLen + suffixLen > totalLen)
            {
                return "IMPOSSIBLE";
            }

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

            int startSuffix = n - suffixLen;

            for (int i = 0; i < suffixLen; ++i)
            {
                int idx = startSuffix + i;

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
            return "IMPOSSIBLE";
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


