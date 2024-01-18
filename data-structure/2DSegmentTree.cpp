struct SegmentTree2d
{
    int n, m;
    vector <vector <int> > t;

    SegmentTree2d(int n, int m) : n(n), m(m)
    {
        t.resize(n << 2, vector <int> (m << 2, 0));
    }

    void UpdateY(int vy, int vx, int lx, int rx, int ly, int ry, int x, int y, int newVal)
    {
        if(ly == ry)
        {
            if(lx == rx)t[vx][vy] = newVal;
            else t[vx][vy] = min(t[vx * 2][vy], t[vx * 2 + 1][vy]);
        }
        else
        {
            int my = (ly + ry) >> 1;
            if(y <= my) UpdateY(vy * 2, vx, lx, rx, ly, my, x, y, newVal);
            else        UpdateY(vy * 2 + 1, vx, lx, rx, my + 1, ry, x, y, newVal);
            t[vx][vy] = min(t[vx][vy * 2], t[vx][vy * 2 + 1]);
        }
    }
    void UpdateX(int vx, int lx, int rx, int x, int y, int newVal)
    {
        if(lx != rx)
        {
            int mx = (lx + rx) >> 1;
            if(x <= mx) UpdateX(vx * 2, lx, mx, x, y, newVal);
            else 		UpdateX(vx * 2 + 1, mx + 1, rx, x, y, newVal);
        }
        UpdateY(1, vx, lx, rx, 1, m, x, y, newVal);
    }

    int QueryY(int vx, int vy, int tly, int try_, int ly, int ry)
    {
        if (ly > ry)  return INT_MAX;
        if (ly == tly && try_ == ry) return t[vx][vy];
        int tmy = (tly + try_) / 2;
        return min(QueryY(vx, vy*2, tly, tmy, ly, min(ry, tmy)), QueryY(vx, vy*2+1, tmy+1, try_, max(ly, tmy+1), ry));
    }
    int QueryX(int vx, int tlx, int trx, int lx, int rx, int ly, int ry)
    {
        if (lx > rx) return INT_MAX;
        if (lx == tlx && trx == rx) return QueryY(vx, 1, 1, m, ly, ry);
        int tmx = (tlx + trx) / 2;
        return min(QueryX(vx*2, tlx, tmx, lx, min(rx, tmx), ly, ry), QueryX(vx*2+1, tmx+1, trx, max(lx, tmx+1), rx, ly, ry));
    }

};
