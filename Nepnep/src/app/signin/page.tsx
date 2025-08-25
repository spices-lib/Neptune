'use client'

import { useActionState } from 'react'
import { authenticate } from '../actions/Auth'
import Link from 'next/link'

export default function Page() {

    const [ errorMessage, formAction, isPending ] = useActionState(
        authenticate,
        undefined
    )

    return (
        <div className='flex min-h-screen items-center justify-center bg-white px-4'>
            <div className='w-full max-w-sm space-y-6'>
                <h1 className='text-center text-2xl font-semibold text-grap-900'>
                    Sign in
                </h1>
                <form
                    action={ formAction }
                    className='space-y-4'
                >
                    <input
                        type='hidden'
                        name='redirectTo'
                        value='/dashboard'
                    >
                    </input>
                    <div className='relative h-fit'>
                        <input
                            id='email'
                            className='w-full rounded-md border border-gray-300 px-3 pb-1 pt-7 text-sm focus:border-black focus:outline-none'
                            type='email'
                            name='email'
                            required
                            autoComplete='email'
                        >
                        </input>
                        <label
                            htmlFor='email'
                            className='pointer-events-none absolute left-3 top-1/2 -translate-y-1/2 text-[12px] text-gray-500 transition-all peer-focus:top-2 peer-focus:text-[12px]'
                        >
                            EMAIL
                        </label>
                    </div>
                    <div className='relative h-fit'>
                        <input
                            id='password'
                            className='w-full rounded-md border border-gray-300 px-3 pb-1 pt-7 text-sm focus:border-black focus:outline-none'
                            type='password'
                            name='password'
                            required
                            minLength={8}
                            autoComplete='current-password'
                        >
                        </input>
                        <label
                            htmlFor='password'
                            className='pointer-events-none absolute left-3 top-1/2 -translate-y-1/2 text-[12px] text-gray-500 transition-all peer-focus:top-2 peer-focus:text-[12px]'
                        >
                            PASSWORD
                        </label>
                    </div>
                    <button
                        disabled={ isPending }
                        className='w-full rounded-md bg-black py-2 text-sm font-medium text-white hover:bg-gray-900 focus:outline-none disabled:cursor-not-allowed disabled:bg-gray-300'
                    >
                        { isPending ? "Logging..." : "Log in" }
                    </button>
                    <p className='text-center text-xs text-gra y-600'>
                        No account?{' '}
                        <Link
                            className='text-blue-400 hover:text-blue-600'
                            href='/signup'
                        >
                            Create one
                        </Link>
                    </p>
                    { errorMessage && (
                        <p className='text-center text-sm text-red-500'>
                            { errorMessage }
                        </p>
                    )}
                </form>
            </div>
        </div>
    )
}