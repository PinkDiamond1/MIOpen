/*******************************************************************************
 *
 * MIT License
 *
 * Copyright (c) 2017 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *******************************************************************************/

#include <miopen/rnn.hpp>
#include <miopen/errors.hpp>
#include <miopen/logger.hpp>
#include <miopen/tensor_ops.hpp>

// TODO: Make miopenConvAlgoPerf_t loggable
// inline std::ostream& operator<<(std::ostream& os, miopenConvAlgoPerf_t) { return os; }

extern "C" miopenStatus_t miopenCreateRNNDescriptor(miopenRNNDescriptor_t* rnnDesc)
{
    //    MIOPEN_LOG_FUNCTION(rnnDesc);
    return miopen::try_([&] { miopen::deref(rnnDesc) = new miopen::RNNDescriptor(); });
}

extern "C" miopenStatus_t miopenInitRNNDescriptor(
    miopenRNNDescriptor_t rnnDesc, miopenRNNMode_t mode, int seqLength, int layer, int bidir)
{

    //    MIOPEN_LOG_FUNCTION(rnnDesc, mode, seqLength, layer, bidir);
    return miopen::try_(
        [&] { miopen::deref(rnnDesc) = miopen::RNNDescriptor(mode, seqLength, layer, bidir); });
}

extern "C" miopenStatus_t miopenGetRNNDescriptor(
    miopenRNNDescriptor_t rnnDesc, miopenRNNMode_t* mode, int* seqLength, int* layer, int* bidir)
{

    //	MIOPEN_LOG_FUNCTION(rnnDesc, mode, seqLength, layer, bidir);
    return miopen::try_([&] {
        miopen::deref(mode)      = miopen::deref(rnnDesc).mode;
        miopen::deref(seqLength) = miopen::deref(rnnDesc).seqLength;
        miopen::deref(layer)     = miopen::deref(rnnDesc).layer;
        miopen::deref(bidir)     = miopen::deref(rnnDesc).bidir;
    });
}

/*
extern "C" miopenStatus_t
miopenGetConvolutionForwardOutputDim(miopenRNNDescriptor_t rnnDesc,
                                     const miopenTensorDescriptor_t inputTensorDesc,
                                     const miopenTensorDescriptor_t filterDesc,
                                     int* n,
                                     int* c,
                                     int* h,
                                     int* w)
{

    MIOPEN_LOG_FUNCTION(rnnDesc, inputTensorDesc, filterDesc, n, c, h, w);
    return miopen::try_([&] {
        miopen::tie_deref(n, c, h, w) = miopen::deref(rnnDesc).GetForwardOutputDim(
            miopen::deref(inputTensorDesc), miopen::deref(filterDesc));
    });
}
*/

extern "C" miopenStatus_t miopenDestroyRNNDescriptor(miopenRNNDescriptor_t rnnDesc)
{
    //    MIOPEN_LOG_FUNCTION(rnnDesc);
    return miopen::try_([&] { delete rnnDesc; });
}

/*
extern "C" miopenStatus_t
miopenConvolutionForwardGetWorkSpaceSize(miopenHandle_t handle,
                                         const miopenTensorDescriptor_t wDesc,
                                         const miopenTensorDescriptor_t xDesc,
                                         const miopenRNNDescriptor_t rnnDesc,
                                         const miopenTensorDescriptor_t yDesc,
                                         size_t* workSpaceSize)
{

    MIOPEN_LOG_FUNCTION(wDesc, yDesc, rnnDesc, workSpaceSize);
    miopen::try_([&] {
        miopen::deref(workSpaceSize) =
            miopen::deref(rnnDesc).ForwardGetWorkSpaceSize(miopen::deref(handle),
                                                            miopen::deref(wDesc),
                                                            miopen::deref(xDesc),
                                                            miopen::deref(yDesc));
    });

    return (miopenStatusSuccess);
}

extern "C" miopenStatus_t
miopenFindConvolutionForwardAlgorithm(miopenHandle_t handle,
                                      const miopenTensorDescriptor_t xDesc,
                                      const void* x,
                                      const miopenTensorDescriptor_t wDesc,
                                      const void* w,
                                      const miopenRNNDescriptor_t rnnDesc,
                                      const miopenTensorDescriptor_t yDesc,
                                      void* y,
                                      const int requestAlgoCount,
                                      int* returnedAlgoCount,
                                      miopenConvAlgoPerf_t* perfResults,
                                      void* workSpace,
                                      size_t workSpaceSize,
                                      bool exhaustiveSearch)
{

    MIOPEN_LOG_FUNCTION(xDesc,
                        x,
                        wDesc,
                        w,
                        rnnDesc,
                        yDesc,
                        y,
                        requestAlgoCount,
                        returnedAlgoCount,
                        perfResults,
                        workSpace,
                        workSpaceSize,
                        exhaustiveSearch);
    return miopen::try_([&] {
        miopen::deref(rnnDesc).FindConvFwdAlgorithm(miopen::deref(handle),
                                                     miopen::deref(xDesc),
                                                     DataCast(x),
                                                     miopen::deref(wDesc),
                                                     DataCast(w),
                                                     miopen::deref(yDesc),
                                                     DataCast(y),
                                                     requestAlgoCount,
                                                     returnedAlgoCount,
                                                     perfResults,
                                                     DataCast(workSpace),
                                                     workSpaceSize,
                                                     exhaustiveSearch);
    });
}

extern "C" miopenStatus_t miopenConvolutionForward(miopenHandle_t handle,
                                                   const void* alpha,
                                                   const miopenTensorDescriptor_t xDesc,
                                                   const void* x,
                                                   const miopenTensorDescriptor_t wDesc,
                                                   const void* w,
                                                   const miopenRNNDescriptor_t rnnDesc,
                                                   miopenConvFwdAlgorithm_t algo,
                                                   const void* beta,
                                                   const miopenTensorDescriptor_t yDesc,
                                                   void* y,
                                                   void* workSpace,
                                                   size_t workSpaceSize)
{

    MIOPEN_LOG_FUNCTION(
        alpha, xDesc, x, wDesc, w, rnnDesc, algo, beta, yDesc, y, workSpace, workSpaceSize);
    return miopen::try_([&] {
        miopen::deref(rnnDesc).ConvolutionForward(miopen::deref(handle),
                                                   alpha,
                                                   miopen::deref(xDesc),
                                                   DataCast(x),
                                                   miopen::deref(wDesc),
                                                   DataCast(w),
                                                   algo,
                                                   beta,
                                                   miopen::deref(yDesc),
                                                   DataCast(y),
                                                   DataCast(workSpace),
                                                   workSpaceSize);
    });
}

extern "C" miopenStatus_t miopenConvolutionForwardBias(miopenHandle_t handle,
                                                       const void* alpha,
                                                       const miopenTensorDescriptor_t bDesc,
                                                       const void* b,
                                                       const void* beta,
                                                       const miopenTensorDescriptor_t yDesc,
                                                       void* y)
{

    MIOPEN_LOG_FUNCTION(alpha, bDesc, b, beta, yDesc, y);
    return miopen::try_([&] {

        return OpTensor(miopen::deref(handle),
                        miopenTensorOpAdd,
                        alpha,
                        miopen::deref(yDesc),
                        DataCast(y),
                        alpha,
                        miopen::deref(bDesc),
                        DataCast(b),
                        beta,
                        miopen::deref(yDesc),
                        DataCast(y));
    });
}

extern "C" miopenStatus_t
miopenFindConvolutionBackwardDataAlgorithm(miopenHandle_t handle,
                                           const miopenTensorDescriptor_t dyDesc,
                                           const void* dy,
                                           const miopenTensorDescriptor_t wDesc,
                                           const void* w,
                                           const miopenRNNDescriptor_t rnnDesc,
                                           const miopenTensorDescriptor_t dxDesc,
                                           const void* dx,
                                           const int requestAlgoCount,
                                           int* returnedAlgoCount,
                                           miopenConvAlgoPerf_t* perfResults,
                                           void* workSpace,
                                           size_t workSpaceSize,
                                           bool exhaustiveSearch)
{

    MIOPEN_LOG_FUNCTION(dyDesc,
                        dy,
                        wDesc,
                        w,
                        rnnDesc,
                        dxDesc,
                        dx,
                        requestAlgoCount,
                        returnedAlgoCount,
                        perfResults,
                        workSpace,
                        workSpaceSize,
                        exhaustiveSearch);
    return miopen::try_([&] {
        miopen::deref(rnnDesc).FindConvBwdDataAlgorithm(miopen::deref(handle),
                                                         miopen::deref(dyDesc),
                                                         DataCast(dy),
                                                         miopen::deref(wDesc),
                                                         DataCast(w),
                                                         miopen::deref(dxDesc),
                                                         DataCast(dx),
                                                         requestAlgoCount,
                                                         returnedAlgoCount,
                                                         perfResults,
                                                         DataCast(workSpace),
                                                         workSpaceSize,
                                                         exhaustiveSearch);
    });
}

extern "C" miopenStatus_t
miopenConvolutionBackwardData(miopenHandle_t handle,
                              const void* alpha,
                              const miopenTensorDescriptor_t dyDesc,
                              const void* dy,
                              const miopenTensorDescriptor_t wDesc,
                              const void* w,
                              const miopenRNNDescriptor_t rnnDesc,
                              miopenConvBwdDataAlgorithm_t algo,
                              const void* beta,
                              const miopenTensorDescriptor_t dxDesc,
                              void* dx,
                              void* workSpace,
                              size_t workSpaceSize)
{

    MIOPEN_LOG_FUNCTION(
        alpha, dyDesc, dy, wDesc, w, rnnDesc, algo, beta, dxDesc, dx, workSpace, workSpaceSize);
    return miopen::try_([&] {
        miopen::deref(rnnDesc).ConvolutionBackwardData(miopen::deref(handle),
                                                        alpha,
                                                        miopen::deref(dyDesc),
                                                        DataCast(dy),
                                                        miopen::deref(wDesc),
                                                        DataCast(w),
                                                        algo,
                                                        beta,
                                                        miopen::deref(dxDesc),
                                                        DataCast(dx),
                                                        DataCast(workSpace),
                                                        workSpaceSize);
    });
}

extern "C" miopenStatus_t
miopenConvolutionBackwardDataGetWorkSpaceSize(miopenHandle_t handle,
                                              const miopenTensorDescriptor_t dyDesc,
                                              const miopenTensorDescriptor_t wDesc,
                                              const miopenRNNDescriptor_t rnnDesc,
                                              const miopenTensorDescriptor_t dxDesc,
                                              size_t* workSpaceSize)
{

    MIOPEN_LOG_FUNCTION(dyDesc, wDesc, rnnDesc, dxDesc, workSpaceSize);
    return miopen::try_([&] {
        miopen::deref(workSpaceSize) =
            miopen::deref(rnnDesc).BackwardDataGetWorkSpaceSize(miopen::deref(handle),
                                                                 miopen::deref(wDesc),
                                                                 miopen::deref(dyDesc),
                                                                 miopen::deref(dxDesc));
    });
}

extern "C" miopenStatus_t
miopenConvolutionBackwardWeightsGetWorkSpaceSize(miopenHandle_t handle,
                                                 const miopenTensorDescriptor_t dyDesc,
                                                 const miopenTensorDescriptor_t xDesc,
                                                 const miopenRNNDescriptor_t rnnDesc,
                                                 const miopenTensorDescriptor_t dwDesc,
                                                 size_t* workSpaceSize)
{

    MIOPEN_LOG_FUNCTION(dyDesc, xDesc, rnnDesc, dwDesc, workSpaceSize);
    return miopen::try_([&] {
        miopen::deref(workSpaceSize) =
            miopen::deref(rnnDesc).ConvolutionBackwardWeightsGetWorkSpaceSize(
                miopen::deref(handle),
                miopen::deref(dyDesc),
                miopen::deref(xDesc),
                miopen::deref(dwDesc));
    });
}

extern "C" miopenStatus_t
miopenFindConvolutionBackwardWeightsAlgorithm(miopenHandle_t handle,
                                              const miopenTensorDescriptor_t dyDesc,
                                              const void* dy,
                                              const miopenTensorDescriptor_t xDesc,
                                              const void* x,
                                              const miopenRNNDescriptor_t rnnDesc,
                                              const miopenTensorDescriptor_t dwDesc,
                                              void* dw,
                                              const int requestAlgoCount,
                                              int* returnedAlgoCount,
                                              miopenConvAlgoPerf_t* perfResults,
                                              void* workSpace,
                                              size_t workSpaceSize,
                                              bool exhaustiveSearch)
{

    MIOPEN_LOG_FUNCTION(dyDesc,
                        dy,
                        xDesc,
                        x,
                        rnnDesc,
                        dwDesc,
                        dw,
                        requestAlgoCount,
                        returnedAlgoCount,
                        perfResults,
                        workSpace,
                        workSpaceSize,
                        exhaustiveSearch);
    return miopen::try_([&] {
        miopen::deref(rnnDesc).FindConvBwdWeightsAlgorithm(miopen::deref(handle),
                                                            miopen::deref(dyDesc),
                                                            DataCast(dy),
                                                            miopen::deref(xDesc),
                                                            DataCast(x),
                                                            miopen::deref(dwDesc),
                                                            DataCast(dw),
                                                            requestAlgoCount,
                                                            returnedAlgoCount,
                                                            perfResults,
                                                            DataCast(workSpace),
                                                            workSpaceSize,
                                                            exhaustiveSearch);
    });
}

extern "C" miopenStatus_t
miopenConvolutionBackwardWeights(miopenHandle_t handle,
                                 const void* alpha,
                                 const miopenTensorDescriptor_t dyDesc,
                                 const void* dy,
                                 const miopenTensorDescriptor_t xDesc,
                                 const void* x,
                                 const miopenRNNDescriptor_t rnnDesc,
                                 miopenConvBwdWeightsAlgorithm_t algo,
                                 const void* beta,
                                 const miopenTensorDescriptor_t dwDesc,
                                 void* dw,
                                 void* workSpace,
                                 size_t workSpaceSize)
{

    MIOPEN_LOG_FUNCTION(
        alpha, dyDesc, dy, xDesc, x, rnnDesc, algo, beta, dwDesc, dw, workSpace, workSpaceSize);
    return miopen::try_([&] {
        miopen::deref(rnnDesc).ConvolutionBackwardWeights(miopen::deref(handle),
                                                           alpha,
                                                           miopen::deref(dyDesc),
                                                           DataCast(dy),
                                                           miopen::deref(xDesc),
                                                           DataCast(x),
                                                           algo,
                                                           beta,
                                                           miopen::deref(dwDesc),
                                                           DataCast(dw),
                                                           DataCast(workSpace),
                                                           workSpaceSize);
    });
}

extern "C" miopenStatus_t miopenConvolutionBackwardBias(miopenHandle_t handle,
                                                        const void* alpha,
                                                        const miopenTensorDescriptor_t dyDesc,
                                                        const void* dy,
                                                        const void* beta,
                                                        const miopenTensorDescriptor_t dbDesc,
                                                        void* db)
{
    return miopen::try_([&] {
        ConvolutionBackwardBias(miopen::deref(handle),
                                alpha,
                                miopen::deref(dyDesc),
                                DataCast(dy),
                                beta,
                                miopen::deref(dbDesc),
                                DataCast(db));
    });
}
*/