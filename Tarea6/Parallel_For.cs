using System;
using System.Threading;
using System.Threading.Tasks;

namespace Task_Parallel
{
    class Program
    {
        static void Main(string[] args)
        {
            //var t1 = Task.Factory.StartNew(() => Dowork(1, 2000)).ContinueWith((prev) => DoOtherWork(1,2000));
            //var t2 = Task.Factory.StartNew(() => Dowork(2, 2500));
            //var t3 = Task.Factory.StartNew(() => Dowork(3, 1500));

            //Console.ReadKey();

            int[] arr = new int[] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

            Parallel.For(0, 10, i =>
             {

                 Console.WriteLine("i = " + i);
                 Thread.Sleep(1000);

             });



            //for (int i = 0; i < 10; i++)
            //{
            //    Console.WriteLine("i = " + i);
            //   Thread.Sleep(1000);
            //}


        }



        //static void Dowork(int id, int sleep)
        //{

        //    Console.WriteLine("Task {0} is beginning...", id);
        //    Thread.Sleep(sleep);
        //    Console.WriteLine("Task {0} is complete....", id);

        //}


        //static void DoOtherWork(int id, int sleep)
        //{

        //    Console.WriteLine("Other Task {0} is beginning...", id);
        //    Thread.Sleep(sleep);
        //    Console.WriteLine("Other Task  {0} is complete....", id);

        //}
    }
}
