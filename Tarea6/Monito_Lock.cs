using System;
using System.Threading;

namespace Parallel_lock
{
    class Program
    {
        static readonly object _object = new object();

        static void TestLock()
        {

            lock (_object)
            {
                Thread.Sleep(100);
                Console.WriteLine(Environment.TickCount);
            }
        }

        static void Main(string[] args)
        {
            for (int i = 0; i < 10; i++)
            {
                ThreadStart start = new ThreadStart(TestLock);
                new Thread(start).Start();
            }

            Console.ReadLine();
        }
    }
}
