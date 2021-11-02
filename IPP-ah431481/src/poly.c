#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "poly.h"
#include "poly_helper.h"

Poly PolyAddMonos(size_t count, const Mono monos[]) {

    if(count==0 || monos == NULL)
        return PolyZero();

    Poly p;
    p.size = count;
    p.arr = malloc(count * sizeof(Mono));

    memcpy(p.arr, monos, sizeof(Mono) * count);

    Sort(&p);
    Simplify(&p, false);

    return p;
}

Poly PolyOwnMonos(size_t count, Mono *monos) {

    if(count == 0 || monos == NULL) {
        if(monos != NULL)
            free(monos);
        return PolyFromCoeff(0);}

    Poly p;
    p.size = count;
    p.arr = monos;


    Sort(&p);
    Simplify(&p, false);

    return p;
}

Poly PolyCloneMonos(size_t count, const Mono monos[]){

    if(count == 0 || monos == NULL)
        return PolyFromCoeff(0);

    Poly p;
    p.size = count;
    p.arr = malloc(count * sizeof(Mono));

    for(size_t i=0; i<p.size; i++) {
        p.arr[i] = MonoClone(&monos[i]);
    }

    Sort(&p);
    Simplify(&p, false);
    return p;
}

void PolyDestroy(Poly *p) {
    assert(p!=NULL);

    if (p->arr == NULL)
        return;
    else {
        for (size_t i = 0; i < p->size; i++) {
            MonoDestroy(&p->arr[i]);
        }
    }
    free(p->arr);
}

Poly PolyClone(const Poly *p) {
    assert(p!= NULL);

    if (PolyIsCoeff(p)) {
        return PolyFromCoeff(p->coeff);

    } else {
        Poly temp;
        temp.arr = safeMalloc(p->size , sizeof(Mono));

        for (size_t i = 0; i < p->size; i++) {
            temp.arr[i] = MonoClone(&p->arr[i]);

        }
        temp.size = p->size;
        return temp;
    }

}


Poly PolyAdd(const Poly *p, const Poly *q) {
    assert(p!=NULL && q!=NULL);

    Poly temp = PolyAddHelper(p, q);

    return temp;
}


Poly PolySub(const Poly *p, const Poly *q) {
    assert(p!=NULL && q!=NULL);

    Poly temp = PolyClone(q);
    PolyNegHelper(&temp);

    Poly res = PolyAddHelper(p, &temp);
    PolyDestroy(&temp);

    return res;
}


Poly PolyMul(const Poly *p, const Poly *q) {
    assert(p!=NULL && q!=NULL);

    if (p->arr == NULL && q->arr == NULL) {
        poly_coeff_t res = p->coeff * q->coeff;
        return PolyFromCoeff(res);
    }
    Poly temp;
    if (p->arr == NULL && q->arr != NULL) {
        temp.size = q->size;
        temp.arr = safeMalloc(temp.size , sizeof(Mono));

        for (size_t i = 0; i < temp.size; i++) {
            temp.arr[i] = MonoClone(&q->arr[i]);
            MultiplicateMonos(&temp.arr[i], p->coeff);
        }

    } else if (p->arr != NULL && q->arr == NULL) {
        temp.size = p->size;
        temp.arr = safeMalloc(temp.size , sizeof(Mono));

        for (size_t i = 0; i < temp.size; i++) {
            temp.arr[i] = MonoClone(&p->arr[i]);
            MultiplicateMonos(&temp.arr[i], q->coeff);
        }
    } else {

        temp.size = p->size * q->size;
        temp.arr = safeMalloc(temp.size , sizeof(Mono));


        for (size_t i = 0; i < p->size; i++) {
            for (size_t j = 0; j < q->size; j++) {
                Mono nowy;
                nowy.exp = p->arr[i].exp + q->arr[j].exp;
                nowy.p = PolyMul(&p->arr[i].p, &q->arr[j].p);
                temp.arr[j + i * q->size] = nowy;
            }
        }

    }
    Sort(&temp);
    Simplify(&temp, true);
    return temp;
}


Poly PolyNeg(const Poly *p) {
    assert(p!=NULL);

    if (!PolyIsCoeff(p)) {
	Poly temp = PolyClone(p);
        for (size_t i = 0; i < temp.size; i++) {
            PolyNegHelper(&temp.arr[i].p);
        }
	return temp;
    } else {
        return PolyFromCoeff(p->coeff * -1);
    }

}


poly_exp_t PolyDeg(const Poly *p) {
    assert(p!=NULL);

    poly_exp_t maxDeg = 0;

    if (p->arr == NULL) {
        if (p->coeff == 0)
            return -1;
        return 0;
    } else {
        for (size_t i = 0; i < p->size; i++) {
            maxDeg = max(maxDeg, PolyDeg(&(p->arr[i].p)) + p->arr[i].exp);
        }
    }
    return maxDeg;
}


poly_exp_t PolyDegBy(const Poly *p, size_t var_idx) {
    assert(p!=NULL);

    poly_exp_t maxDegBy = -1;

    if (p->arr == NULL) {
        if (p->coeff == 0)
            return -1;
        return 0;

    } else {
        for (size_t i = 0; i < p->size; i++) {

            if (var_idx == 0 && p->arr[i].exp > maxDegBy)
                maxDegBy = p->arr[i].exp;

            else {
                if(var_idx != 0)
                maxDegBy = max(maxDegBy, PolyDegBy(&(p->arr[i].p), var_idx - 1));
            }

        }
    }
    return maxDegBy;
}


bool PolyIsEq(const Poly *p, const Poly *q) {
    assert(p!=NULL && q!=NULL);

    bool res = isTheSame(q, p);
    return res;

}

Poly PolyAt(const Poly *p, poly_coeff_t x) {
    assert(p!=NULL);

    if (p->arr == NULL)
        return PolyClone(p);
    Poly nowy = PolyClone(p);
    Poly res = PolyFromCoeff(0);

    for (size_t i = 0; i < nowy.size; i++) {

        if (nowy.arr[i].p.arr == NULL) {

            poly_coeff_t xi = (poly_coeff_t)BinPower(x, nowy.arr[i].exp);
            nowy.arr[i].exp = 0;
            nowy.arr[i].p.coeff *= xi;

            Poly temp = res;
            res = PolyAdd(&res, &nowy.arr[i].p);
            PolyDestroy(&temp);
        }

        else {
            MultiplicateMonos(&nowy.arr[i], BinPower( x, nowy.arr[i].exp));
            nowy.arr[i].exp = 0;
            Poly temp = res;
            res = PolyAdd(&res, &nowy.arr[i].p);
            PolyDestroy(&temp);
        }
    }
    Sort(&res);
    Simplify(&res, true);
    PolyDestroy(&nowy);
    return res;
}




Poly PolyCompose2(const Poly *p, size_t k, const Poly q[], size_t take);

Poly PolyCompose(const Poly *p, size_t k, const Poly q[]) {
    assert(p!=NULL);

    if(p->arr == NULL)
        return PolyClone(p);

    size_t take = 0;
    Poly res = PolyCompose2(p, k, q, take);

    Sort(&res);
    Simplify(&res, true);
    return res;
}



Poly PolyCompose2(const Poly *p, size_t k, const Poly q[], size_t take) {
    assert(p!=NULL);

    if(p->arr == NULL) {
        return PolyClone(p);
    }

    Poly res = PolyZero();

    for(size_t i=0; i<p->size; i++) {


        Poly actual, next;
        if (p->arr[i].exp > 0 && k>0) {
            actual = PolyPower(&q[take], p->arr[i].exp);
            next = PolyCompose2(&p->arr[i].p, k-1, q, take+1);
        } else if (p->arr[i].exp == 0 && k>0) {
                actual = PolyFromCoeff(1);

           if(k>0)
               next = PolyCompose2(&p->arr[i].p, k-1, q, take+1);

        } else if(k == 0) {
            if(p->arr[i].exp == 0 && PolyIsCoeff(&p->arr[i].p)) {
                res = PolyClone(&p->arr[i].p);
                return res;
            }
            actual = PolyZero();
            next = PolyZero();
            res = PolyZero();

        }

        Poly temp1 = actual;
        actual = PolyMul(&actual, &next);
        PolyDestroy(&temp1);

        Poly temp2 = res;
        res = PolyAdd(&res, &actual);
        PolyDestroy(&temp2);
        PolyDestroy(&next);
        PolyDestroy(&actual);

    }
        return res;
}
