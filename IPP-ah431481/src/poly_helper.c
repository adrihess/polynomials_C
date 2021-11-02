#include "poly.h"
#include "poly_helper.h"
#include <stdlib.h>
#include <assert.h>


long max(long a, long b) {

    if (a > b)
        return a;
    return b;
}


void Simplify(Poly *p, bool deepSimplify) {
    assert(p!=NULL);

    if (p->arr == NULL)
        return;

    size_t rozm=0;
    size_t i=0;
    while (i < p->size) {

        if (PolyIsZero(&p->arr[i].p)) {
            i++;
        }
        else  {
            poly_exp_t exp = MonoGetExp(&p->arr[i]);
            Poly temp=p->arr[i].p;
            i++;

            while(i<p->size &&  exp == MonoGetExp(&p->arr[i])) {
                Poly temp2 = temp;
            temp = PolyAddHelper(&temp, &p->arr[i].p);
            PolyDestroy(&temp2);
            PolyDestroy(&p->arr[i].p);
            i++;
            }

            if(!PolyIsZero(&temp)) {
            rozm++;
            p->arr[rozm-1] = MonoFromPoly(&temp, exp);}

        }
    }

    if(rozm == 0) {
        free(p->arr);
        *p = PolyZero();
        return;
    }

    if(rozm != p->size) {

        p->size = rozm;
        p->arr = realloc(p->arr, rozm * sizeof(Mono));

    }

    for(size_t ir=0; deepSimplify && ir<p->size; ir++) {
        Simplify(&p->arr[ir].p, true);
    }


}


int CompareExps(const void *m1, const void *m2) {
    assert(m1!=NULL && m2!=NULL);
    if (MonoGetExp(m1) < MonoGetExp(m2))
        return 1;
    else if (MonoGetExp(m1) == MonoGetExp(m2)) return 0;
    else
        return -1;
}



void Sort(Poly *p) {
    assert(p!=NULL);

    if (p->arr == NULL)
        return;

    qsort(p->arr, p->size, sizeof(Mono), CompareExps);


    for (size_t i = 0; i < p->size && p->arr[i].p.arr != NULL ; i++) {
        Sort(&p->arr[i].p);
    }


}


void MultiplicateMonos(Mono *m, poly_coeff_t x) {
    assert(m!=NULL);

    if (m->p.arr == NULL) {
        m->p.coeff *= x;
        return;
    } else {
        for (size_t i = 0; i < m->p.size; i++) {
            MultiplicateMonos(&m->p.arr[i], x);
        }
    }
}


long BinPower(long a, long b) {
    assert(b>=0);

    if (b == 0)
        return 1;
    if (b == 1)
        return a;

    long res = 1;

    while (b > 0) {

        if (b % 2 == 1)
            res *= a;

        b /= 2;
        a *= a;
    }
    return res;
}


void PolyNegHelper(Poly *p) {
    assert(p!=NULL);
    if (!PolyIsCoeff(p)) {
        for (size_t i = 0; i < p->size; i++) {
            PolyNegHelper(&p->arr[i].p);
	}
    } else {
        p->coeff *= -1;
	return; }

}



Poly PolyAddHelper(const Poly *p, const Poly *q) {
    assert(p!=NULL && q!=NULL);

    if (p->arr == NULL && q->arr == NULL) {
        return PolyFromCoeff(p->coeff + q->coeff);
    }
    Poly temp;
    if (p->arr == NULL || q->arr == NULL) {
        const Poly *wsk;
        const Poly *wsk2;
        (p->arr != NULL) ? (wsk = p, wsk2 = q) : (wsk = q, wsk2 = p);

        poly_exp_t exp = 0;

        if(PolyIsZero(p))
            return PolyClone(q);
        if(PolyIsZero(q))
            return PolyClone(p);

        temp.size = wsk->size;
        temp.arr = malloc(temp.size * sizeof(Mono));
        for (size_t i = 0; i < wsk->size; i++) {
            temp.arr[i] = MonoClone(&wsk->arr[i]);
        }

        if(temp.arr[temp.size-1].exp == 0  ) {
            if(PolyIsCoeff(&temp.arr[temp.size-1].p)) {
                temp.arr[temp.size-1].p.coeff += wsk2->coeff;
                if(temp.arr[temp.size-1].p.coeff == 0) {
                    PolyDestroy(&temp.arr[temp.size-1].p);
                    temp.size--;
                    temp.arr = safeRealloc(temp.arr, temp.size, sizeof(Mono));

                    if(temp.size == 0)
                    {
                        temp.arr = NULL;
                        temp.coeff = 0;
                    }
                }
                return temp;
            }

            Poly wsk5 = temp.arr[temp.size-1].p;
            temp.arr[temp.size-1].p = PolyAddHelper(&temp.arr[temp.size-1].p , wsk2);
            PolyDestroy(&wsk5);
            return temp;
        }

        temp.size += 1;
        temp.arr = realloc(temp.arr, temp.size * sizeof(Mono));

        temp.arr[temp.size - 1] = (Mono) {

                .exp = exp,
                .p = PolyFromCoeff(wsk2->coeff)
        };

    } else {

        const Poly *wsk;
        const Poly *wsk2;

        wsk = p;
        wsk2 = q;

        size_t max_size = 2;
        temp.arr=malloc(max_size * sizeof(Mono));
        size_t i=0, j=0;

        size_t poz=0;
        Mono res;

        while(i<wsk->size && j<wsk2->size) {

            if(wsk->arr[i].exp == wsk2->arr[j].exp) {
                Poly res2 = PolyAddHelper(&wsk->arr[i].p, &wsk2->arr[j].p);
                res.p = res2;
                res.exp = wsk->arr[i].exp;
                i++;
                j++;
            }
            else if(wsk->arr[i].exp > wsk2->arr[j].exp) {
                res = MonoClone(&wsk->arr[i]);
                i++;
            }
            else if(wsk->arr[i].exp < wsk2->arr[j].exp) {
                res = MonoClone(&wsk2->arr[j]);
                j++;
            }

            if(!PolyIsZero(&res.p)) {
                if(poz >= max_size) {
                    max_size *= 2;
                    temp.arr = realloc(temp.arr, max_size * sizeof(Mono));
                }

                temp.arr[poz] = res;
                poz++;
            }

        }

        while(i<wsk->size) {
            res = MonoClone(&wsk->arr[i]);
            i++;

            if(!PolyIsZero(&res.p)) {
                if(poz >= max_size) {
                    max_size *= 2;
                    temp.arr = realloc(temp.arr, max_size * sizeof(Mono));
                }

                temp.arr[poz] = res;
                poz++;
            }
        }

        while(j<wsk2->size) {
            res = MonoClone(&wsk2->arr[j]);
            j++;

            if(!PolyIsZero(&res.p)) {
                if(poz >= max_size) {
                    max_size *= 2;
                    temp.arr = realloc(temp.arr, max_size * sizeof(Mono));
                }

                temp.arr[poz] = res;
                poz++;
            }
        }
        temp.size = poz;
        temp.arr = realloc(temp.arr, poz * sizeof(Mono));
    }
    return temp;
}



bool isTheSame(const Poly *p,const Poly *q) {
    assert(p!=NULL && q!=NULL);

    if (p == q)
        return true;

    if (p->arr == NULL && q->arr == NULL) {
        return p->coeff == q->coeff;
    }
    if (p->arr == NULL || q->arr == NULL) {
        const Poly *wsk;
        const Poly *wsk2;
        (p->arr == NULL) ? (wsk = p, wsk2 = q) : (wsk = q, wsk2 = p);

        if (wsk2->size == 1 && wsk2->arr[0].exp == 0 )
            return isTheSame(wsk, &wsk2->arr[0].p);
        else
            return false;
    }

    if (p->size != q->size)
        return false;

    for (size_t i = 0; i < p->size; i++) {
        if (p->arr[i].exp != q->arr[i].exp)
            return false;
        if (!isTheSame(&(p->arr[i].p), &(q->arr[i].p)))
            return false;
    }
    return true;
}

Poly PolyPower(const Poly *p, int exp) {
    assert(p!=NULL && exp > 0);
    Poly res = PolyClone(p);
    while(exp > 1) {
        Poly res_destr = res;
        res = PolyMul(&res, p);
        PolyDestroy(&res_destr);
        exp--;
    }
    return res;
}