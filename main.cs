#pragma warning disable CS8602
#pragma warning disable CS8604
#pragma warning disable CS0162
using System;
using System.Collections.Generic;
using System.Threading;
using System.Diagnostics;


namespace ctf;

public static class Program
{
    internal static class Functions
    {
        public static T Identity<T>(T arg) => arg;
    }
    private static string[] Read() => Console.ReadLine().Select(x => new string(new[] { x })).ToArray();

    private static long[] ReadL(Func<long, long>? a = null) =>
        Console.ReadLine()
            .Split(" ")
            .Select(x => a is null ? long.Parse(x) : a(long.Parse(x)))
            .ToArray();

    private static int[] ReadI(Func<int, int>? a = null) =>
        Console.ReadLine()
            .Split(" ")
            .Select(x => a is null ? int.Parse(x) : a(int.Parse(x)))
            .ToArray();

    private static ulong[] ReadUL(Func<ulong, ulong>? a = null) =>
        Console.ReadLine()
            .Split(" ")
            .Select(x => a is null ? ulong.Parse(x) : a(ulong.Parse(x)))
            .ToArray();

    private static (int val, int ind)[] ReadII(int i = 0) =>
        Console.ReadLine().Split(" ").Select(x => (int.Parse(x), i++)).ToArray();

    private static (long val, int ind)[] ReadLI(int i = 0) =>
        Console.ReadLine().Split(" ").Select(x => (long.Parse(x), i++)).ToArray();

    private static void Write<T>(IEnumerable<T> a, string sep = " ") => Console.WriteLine(string.Join(sep, a));
    private static int ReverseComp<T, U>(T x, T y, Func<T, U> func) where U : IComparable => -1 * func(x).CompareTo(func(y));
    private static int ReverseComp<T>(T x, T y) where T : IComparable => -1 * x.CompareTo(y);
    
    
    
    public static void Main(string[] args)
    {
        using var input = new StreamReader(
            Console.OpenStandardInput(),
            Console.InputEncoding,
            detectEncodingFromByteOrderMarks: false,
            bufferSize: 65536);  

        using var output = new StreamWriter(
            Console.OpenStandardOutput(),
            Console.OutputEncoding,
            bufferSize: 65536)
        {
            AutoFlush = false   
        };
        Console.SetIn(input);
        Console.SetOut(output);
        long TEST_COUNT = 1;
        if (MULTITEST)
        {
            TEST_COUNT = ReadL()[0];
        }
        
#if ONLINE_JUDGE
        for (long TEST = 1; TEST <= TEST_COUNT; ++TEST)
        {
           Solve(); 
        }
#else
        Stopwatch stopwatch = new Stopwatch();
        for (long TEST = 1; TEST <= TEST_COUNT; ++TEST)
        {
            Console.WriteLine($"=== TEST {TEST} ===");
            stopwatch.Start();
            Solve();
            stopwatch.Stop();
            Console.WriteLine($"Time: {stopwatch.ElapsedMilliseconds * 1.0 / 1000.0}s");
            stopwatch.Reset();
        }
#endif
    }


    private const bool MULTITEST = true;
    
    private static void Solve()
    {
        var n = ReadI()[0];
        var a = ReadI();
        var list = new List<(int x, int y)>();
        Array.Sort(a);
        for(int i = 0; i < a.Length - 1; ++i) list.Add((a[i], a[i+1]));
        list.Add((a[^1], a[0]));
        int k = 0;
        list.Sort((p1, p2) => ReverseComp(p1,p2, new Func<(int x, int y),int>(((int,int) p) => Len(n, p))));

        int count = n;
        foreach (var seg in list)
        {
            int len = Len(n, seg) - 2 * k;
            if (len <= 0) continue;
            count -= len;
            count += len == 1 ? 0 : 1;
            k += 2;
        }
        Console.WriteLine(count);
    }

    private static int Len(int n, (int x, int y) seg)
    {
        if (seg.y > seg.x) return seg.y - seg.x - 1;
        return n - (seg.x - seg.y + 1);
    }
}

