
import argparse
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

def main(args):
    df  = pd.read_csv(args.log, sep=" ", header=0)
    df = df[['method', 'N','clk(ini)', 'clk(mult)', 'User(s)', 'Real(s)']] #

    ini_plus_mult = df['clk(ini)'] + df['clk(mult)']
    print('ini+mult\n',ini_plus_mult)

    print('user\n',df['User(s)'])

    dif = ini_plus_mult - df['Real(s)']# df['User(s)']
    print('avg diff:',np.mean(dif), np.mean(df['User(s)']))


    # Difference in initialization:
    print('seq ini times:', df[df['method']=="sequential"]['clk(ini)'].values)
    div = df[df['method']=="my_eigen_matmult"]['clk(ini)'].values / df[df['method']=="sequential"]['clk(ini)'].values
    print('with nans', div)
    div = div[~ np.isnan(div)]
    print('without nans', div)
    print('ini (seq/eigen) mean, median, std:', np.mean(div), np.median(div), np.std(div))


    # Difference between mult and ini:
    mult = df[df['method']=="sequential"]['clk(mult)'].values
    m_i_seq = mult / (mult + df[df['method']=="sequential"]['clk(ini)'].values)
    mult = df[df['method']=="my_eigen_matmult"]['clk(mult)'].values
    m_i_eigen = mult / (mult + df[df['method']=="my_eigen_matmult"]['clk(ini)'].values)
    print('seq (mult/total) mean, median, std:', np.mean(m_i_seq), np.median(m_i_seq), np.std(m_i_seq))
    print('eigen (mult/total) mean, median, std:', np.mean(m_i_eigen), np.median(m_i_eigen), np.std(m_i_eigen))
    exit(0)
    #print(df[df['method']=="sequential"]['N'])

    # plt.figure()

    # PLOT:
    fig, ax = plt.subplots()
    ax.scatter(x=df[df['method']=="sequential"]['N'], y=df[df['method']=="sequential"]['clk(ini)'], label="sequential initialization")
    # ax.scatter(x=df[df['method']=="sequential"]['N'], y=df[df['method']=="sequential"]['clk(mult)'], label="sequential multiplication")


    ax.scatter(x=df[df['method']=="my_eigen_matmult"]['N'], y=df[df['method']=="my_eigen_matmult"]['clk(ini)'], label="eigen initialization")
    # ax.scatter(x=df[df['method']=="my_eigen_matmult"]['N'], y=df[df['method']=="my_eigen_matmult"]['clk(mult)'], label="eigen multiplication")

    # Plt configuration
    ax.legend()
    ax.set_xlabel("N")
    ax.set_ylabel("t (s)")
    ax.set_title("clk time - N for each method")
    ax.grid()
    plt.savefig('clk-ini-times.png')
    #
    # axes = plt.gca()
    # y = np.polyfit(df[df['method']=="sequential"]['N'].values.flatten(), df[df['method']=="sequential"]['User(s)'].values.flatten(), deg=3)
    # X_plot = np.linspace(axes.get_xlim()[0],axes.get_xlim()[1],100)
    # y_plot = X_plot**3*y[0]+X_plot**2*y[1]+X_plot*y[2]+y[3]
    # plt.plot(X_plot, y_plot, '-')

    # ax.legend()

    # ax.scatter(x=df[df['method']=="my_eigen_matmult"]['N'], y=df[df['method']=="my_eigen_matmult"]['User(s)'], label="eigen_vectorization")
    # y = np.polyfit(df[df['method']=="my_eigen_matmult"]['N'].values.flatten(), df[df['method']=="my_eigen_matmult"]['User(s)'].values.flatten(), deg=2)
    # X_plot = np.linspace(axes.get_xlim()[0],axes.get_xlim()[1],100)
    # #
    # # axes = plt.gca()
    # y_plot = X_plot**2*y[0]+X_plot*y[1]+y[2]
    # plt.plot(X_plot, y_plot, '-')
    #
    # # ax.legend()
    #
    # # axes = plt.gca()
    # y_plot = X_plot**2*y[0]+X_plot*y[1]+y[2]
    # plt.plot(X_plot, y_plot, '-')



    # etc.

if __name__ == "__main__":
    parser = argparse.ArgumentParser()

    parser.add_argument('-l', '--log', help='log',
                        type=str, default="src/p2-logs/clock.log")

    args = parser.parse_args()
    main(args)
