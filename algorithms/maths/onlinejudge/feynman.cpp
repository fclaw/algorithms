/** https://onlinejudge.org/external/121/12149.pdf, finding the pattern; square numbers */

namespace algorithms::maths::onlinejudge::feynman
{
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) assert(std::freopen(file.value(), "r", stdin) != nullptr);

        int n;
        while(std::cin >> n)
        {
            if(n == 0) break;
            int ans = 0;
            for(int i = 0; i <= n; i++)
              ans += i * i;
            printf("%d\n", ans);   
        }
    }
}