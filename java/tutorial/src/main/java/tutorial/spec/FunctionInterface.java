package tutorial.spec;


/**
 * A functional interface is an interface that has just one abstract
 * method (aside from the methods of Object), and thus represents a single
 * function contract. This "single" method may take the form of multiple
 * abstract methods with override-equivalent signatures inherited from 
 * superinterfaces; in this case, the inherited methods logically represent
 * a single method.
 * <p>
 * For an interface I, let M be the set of abstract methods that are members
 * of I that do not have the same signature as any public instance method of
 * the class Object. Then, I is a functional interface if there exists a
 * method m in M for which both of the following are true:
 * <ol><li value="1">The signature of m is a subsignature (§8.4.2) of every method's 
 *     signature in M.</li>
 * <li>m is return-type-substitutable (§8.4.5) for every method in M.</li></ol>
 */
@FunctionalInterface
public interface FunctionInterface<T,R> {
    R run(T arg);
}

/**
 * It is not afunction inferface. The equals is method of Object, so it
 * doesn't include a abstract method asdide from Object
 * 
 */
interface NonFunc {
    boolean equals(Object other);
}

/**
 * It is a function inferface. The compare is signle abstract method asdide
 * from Object
 */
@FunctionalInterface
interface Func extends NonFunc {
    int compare(String o1, String o2);
}

/**
 * It is a function inferface. The compare is single abstract method asdide
 * from Object, the equals is method of Object.
 */
@FunctionalInterface
interface Comparator<T> {
    boolean equals(Object obj);
    int compare(T o1, T o2);
}

/**
 * It is a not function inferface. While the compare is single abstract
 * method asdide from Object, the clone is protected method of Object
 * instead of public method
 */
interface ComparatorNew<T> {
    int compare(T o1, T o2);
    Object clone();
}

/**
 * It is a function inferface. While the clone is single abstract method and
 * it is protected method of Object instead of public method
 */
@FunctionalInterface
interface ComparatorNew2<T> {
    Object clone();
}

/**
 * It is a not function inferface. The are no abstract method
 */
interface ComparatorNew3<T> {
}

/**
 * It is a not function inferface. The are no abstract method
 */
interface ComparatorNew4<T> {
    default int compare(T o1, T o2){
        return  o1.equals(o2) ? 0 : 1;
    }
}


@FunctionalInterface interface X1 { int m(Iterable<String> arg); }
@FunctionalInterface interface Y1 { int m(Iterable<String> arg); }
/**
 * It is a function inferface. Because the abstract method of X1, Y1 are
 * same signature
 */
@FunctionalInterface interface Z1 extends X1, Y1 {}


@FunctionalInterface interface X2 { Iterable m(Iterable<String> arg); }
@FunctionalInterface interface Y2 { Iterable<String> m(Iterable arg); }
/**
 * It is a function inferface. Z is a functional interface in the following
 * interface hierarchy because Y.m is a subsignature of X.m and is
 * return-type-substitutable for X.m:
 */
@FunctionalInterface interface Z2 extends X2, Y2 {}

@FunctionalInterface interface X3 { int m(Iterable<String> arg); }
@FunctionalInterface interface Y3 { int m(Iterable<Integer> arg); }
/**
 * It is a function inferface. The method m(Iterable<Integer>) of type
 * Y3 has the same erasure as m(Iterable<String>) of type X3 but does
 * not override it
 */
// interface Z3 extends X3, Y3 {}


@FunctionalInterface interface X4 { int m(Iterable<String> arg, Class c); }
@FunctionalInterface interface Y4 { int m(Iterable arg, Class<?> c); }
// interface Z4 extends X4, Y4 {}


@FunctionalInterface interface X5<T> { void m(T arg); }
@FunctionalInterface interface Y5<T> { void m(T arg); }
//interface Z5<A, B> extends X5<A>, Y5<B> {}
@FunctionalInterface interface Z6<A> extends X5<A>, Y5<A> {}

interface X7 { long m(); }
interface Y7 { int  m(); }
// interface Z7 extends X7, Y7 {}


/**
 * It is not a function inferface. 
 */
interface Foo<T, N extends Number> {
    void m(T arg);
    void m(N arg);
}

/**
 * It is not a function inferface. 
 */
interface Bar extends Foo<String, Integer> {}

/**
 * It is a function inferface. 
 */
@FunctionalInterface interface Baz extends Foo<Integer, Integer> {}




interface Action<T> {}

/**
 * It is a function inferface. 
 */
@FunctionalInterface interface Exec1 { <T> T execute(Action<T> a); }


@FunctionalInterface interface X8 { <T> T execute(Action<T> a); }
@FunctionalInterface interface Y8 { <S> S execute(Action<S> a); }
/**
 * It is a function inferface. signatures are logically "the same"
 */
@FunctionalInterface interface Exec2 extends X8, Y8 {}


@FunctionalInterface interface X9 { <T>   T execute(Action<T> a); }
@FunctionalInterface interface Y9 { <S,T> S execute(Action<S> a); }
/**
 * complie error, different signatures, same erasure
 */
//interface Exec3 extends X9, Y9 {}

