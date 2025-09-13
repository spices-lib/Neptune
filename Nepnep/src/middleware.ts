import { NextResponse } from 'next/server'
import type { NextRequest } from 'next/server'

export function middleware(request: NextRequest) {

    const hasAuthSession = request.cookies.has('authjs.session-token')
    const isSignInPage = request.nextUrl.pathname === '/signin'
    
    if (!isSignInPage && !hasAuthSession) {
        const url = new URL('/signin', request.url)
        return NextResponse.redirect(url)
    }

    return NextResponse.next()
}

export const config = {
    matcher: ['/dashboard', '/dashboard/:path*']
}